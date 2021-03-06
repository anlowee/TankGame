#include "displaywindow.h"
#include "ui_displaywindow.h"
#include "mymap.h"
#include "Windows.h"
#include <QPainter>
#include <QPixmap>
#include <QStyleOption>
#include <QImage>
#include <QTime>
#include <QKeyEvent>
#include <QSoundEffect>
#include <iostream>
#include <stdlib.h>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QtCore>
#include "myfactory.h"
#include "myglobal.h"
#include "myplayer.h"
#include "mybullet.h"
#include "myenemy.h"
#define BLOOD 30
#define COLLIDEFIX 4
#define MARSHSPEED 1
#include "selectlevelwindow.h"
int DisplayWindow::keyValue;
bool DisplayWindow::b_isTPM;
int cntKill2p;
bool b_factoryboom;

//0-1p win
//1-2p win
int flagwin;

struct BoomPos
{
    int x, y, time;
    bool b_isBoom;
} s_boomPos[1000];

MyBullet a_Bullets[100000];
extern MyEnemy a_EnemyTank[1000];

inline void DeleteBullets(MyBullet*, int, int&);
inline void DeleteTank(MyEnemy*, int, int&);
inline bool IsOutofRange(int, int, int, int, int&);
inline int IsCollide(int, int, int&);
inline int Is2PCollide(int, int, int&);
inline int IsEnemyCollide(int, int, int, int&);


DisplayWindow::DisplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);

    //is hide 2p parameter
    if (!b_isTPM)
    {
        ui->lbl_2Phealth->setVisible(false);
        ui->lbl_2Pkillenemy->setVisible(false);
        ui->lbl_2Pmoney->setVisible(false);
        ui->label_12->setVisible(false);
        ui->label_13->setVisible(false);
        ui->label_14->setVisible(false);
        ui->label_15->setVisible(false);
        ui->label_16->setVisible(false);
        ui->label_17->setVisible(false);
    }

    flagwin = -1;
    cntKill2p = 0;
    b_factoryboom = false;

    setFocusPolicy(Qt::StrongFocus);

    //qDebug() << isTPM;

    //set fps
    QTimer *new_t = new QTimer;
    connect(new_t, SIGNAL(timeout()), this, SLOT(update()));
    new_t->start(1);

    //set enemy atk frequency
    QTimer *enemyAtk = new QTimer;
    connect(enemyAtk, SIGNAL(timeout()), this, SLOT(EnemyAtk()));
    enemyAtk->start(750);

    //set player atk max frequency
    QTimer *playerAtk = new QTimer;
    connect(playerAtk, SIGNAL(timeout()), this, SLOT(PlayerAtk()));
    playerAtk->start(MyPlayer::plyAtkSpeed);

    //set player2 atk max frequency
    if (b_isTPM)
    {
        QTimer *player2Atk = new QTimer;
        connect(player2Atk, SIGNAL(timeout()), this, SLOT(Player2Atk()));
        player2Atk->start(MyPlayer::plyAtkSpeed);
    }


    NextSpawnTime=QDateTime::currentDateTime().addSecs(8+rand()%8);


    //set enemy creat frequency
    QTimer *enemyCreat = new QTimer;
    connect(enemyCreat, SIGNAL(timeout()), this, SLOT(EnemyCreate()));
    enemyCreat->start(100);

}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    //display parameter
    if (MyFactory::ftrHlt < 0)
        MyFactory::ftrHlt = 0;
    ui->lbl_health->setNum(MyPlayer::plyHlt);
    ui->lbl_money->setNum(MyPlayer::plyMoney);
    ui->lbl_killenemy->setNum(cntKill - cntKill2p);
    ui->lbl_factoryhlt->setNum(MyFactory::ftrHlt);
    ui->lbl_enemyremain->setNum(cntEnemy);

    if (b_isTPM)
    {
        ui->lbl_2Phealth->setNum(MyPlayer::ply2Hlt);
        ui->lbl_2Pmoney->setNum(MyPlayer::ply2Money);
        ui->lbl_2Pkillenemy->setNum(cntKill2p);
    }

    //you win game
    if (MyFactory::ftrHlt <= 0 && cntEnemy == 0 && !DisplayWindow::b_isTPM)
    {
        MyPlayer::plyKill += cntKill - cntKill2p;
        MyGlobal::SaveData();
        close();
        QMessageBox::information(this, "Congratulation!", "YOU WIN");
        return;
    }
    //you lost
    if (!DisplayWindow::b_isTPM)
    {
        //single mode lost
        int x = MyPlayer::plyX;
        int y = MyPlayer::plyY;
        if (MyPlayer::plyHlt <= 0)
        {
            p.drawImage(x, y, MyGlobal::imgTankBoom);
            close();
            QMessageBox::information(this, "Haw", "YOU LOST");
            return ;
        }
    }
    else
    {
        //TWO-PLAYER who win
        int x = MyPlayer::plyX;
        int y = MyPlayer::plyY;
        if (MyPlayer::plyHlt <= 0 || flagwin == 1)
        {
            p.drawImage(x, y, MyGlobal::imgTankBoom);
            close();
            QMessageBox::information(this, "1P LOST", "2P WIN");
            return ;
        }

        x = MyPlayer::ply2X;
        y = MyPlayer::ply2Y;
        if (MyPlayer::ply2Hlt <= 0 || flagwin == 0)
        {
            p.drawImage(x, y, MyGlobal::imgTankBoom);
            MyGlobal::SaveData();
            close();
            QMessageBox::information(this, "2P LOST", "1P WIN");
            return ;
        }

    }

    //paint Map
    PaintMap(p);

    //Move Player
    MoveTank(p);

    //Move 2P
    if (b_isTPM)
        MoveTank2P(p);

    //Move Enemy
    MoveEnemyTank(p);

    //Move Bullets
    MoveBullet(p);
}

void DisplayWindow::keyPressEvent(QKeyEvent *event)
{
    keyValue = event->key();
}

void DisplayWindow::PaintMap(QPainter &p)
{
    //paint map
    qsrand(time(NULL));
    for (int i = 0; i < INUM; i++)
        for (int j = 0; j < JNUM; j++)
        {
            char n = MyGlobal::logicMap[i][j];
            int x = j*PICWIDTH, y = i*PICHEIGHT;

            switch (n)
            {
                case 'G':p.drawImage(x, y, MyGlobal::imgGrass); break;
                case 'R':p.drawImage(x, y, MyGlobal::imgRock); break;
                case 'M':p.drawImage(x, y, MyGlobal::imgMarsh); break;
                default:p.drawImage(x, y, MyGlobal::imgGrass);
            }

            //is there a blood or money or factory
            if (MyGlobal::objMap[i][j] == 1)
                p.drawImage(x, y, MyGlobal::imgBlood);
            if (MyGlobal::objMap[i][j] == 2)
                p.drawImage(x, y, MyGlobal::imgCoin);

            //is factory boom
            if (MyGlobal::objMap[i][j] == 3)
            {
                if (b_factoryboom)
                    p.drawImage(x, y, MyGlobal::imgFactoryBoom);
                else
                    p.drawImage(x, y, MyGlobal::imgFactory);
                double percent = 0;
                if (MyFactory::ftrHlt <= 0)
                {
                    percent = 0;
                    b_factoryboom = true;
                }
                else
                    percent = MyFactory::ftrHlt/FACTORYHEALTH;
                QRectF target(x, y - 8, percent*PICWIDTH, 8);
                p.drawImage(target, MyGlobal::imgHealth);
            }

            //random create blood&money
            int ran = rand()%10000000;
            if (ran < 2 && MyGlobal::boolMap[i][j] && MyGlobal::dfsMap[i][j] == MyGlobal::m_TrueBlockMark && MyGlobal::objMap[i][j] == 0)
                MyGlobal::objMap[i][j] = 1;
            else
            if (ran < 4 && MyGlobal::boolMap[i][j] && MyGlobal::dfsMap[i][j] == MyGlobal::m_TrueBlockMark && MyGlobal::objMap[i][j] == 0)
                MyGlobal::objMap[i][j] = 2;
        }
}

void DisplayWindow::MoveTank(QPainter &p)
{

    //paint current pos&dir
    int &x = MyPlayer::plyX;
    int &y = MyPlayer::plyY;
    int &d = MyPlayer::plyD;

    //blood display
    double percent = MyPlayer::plyHlt/MyPlayer::plyMaxHlt;
    QRectF target(x, y - 8, percent*PICWIDTH, 8);
    p.drawImage(target, MyGlobal::img1PHlt);

    switch (d)
    {
        case 0:p.drawImage(x, y, MyPlayer::imgTankUp); break;
        case 1:p.drawImage(x, y, MyPlayer::imgTankDown); break;
        case 2:p.drawImage(x, y, MyPlayer::imgTankLeft); break;
        case 3:p.drawImage(x, y, MyPlayer::imgTankRight); break;
    }

    int n_isCollide = IsCollide(x, y, cntEnemy);

    //react keyPessEvent
    if(::GetAsyncKeyState('W') & 0x8000)
    {
        //set player's status
        b_isPlayerStart = true;
        d = 0;

        //is player coliide the map(rock)
        bool b_isCollideMap = MyGlobal::boolMap[(y - MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - MyPlayer::plySpeed + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        //is player on Marsh(slow down)
        bool b_isOnMarsh = (MyGlobal::logicMap[(y - MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - MyPlayer::plySpeed + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        //control slow down speed
        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = MARSHSPEED;

        //move
        if (y - MyPlayer::plySpeed + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 0)
        {
            p.drawImage(x, y - MyPlayer::plySpeed + additionalSpeed, MyPlayer::imgTankUp);
            y -= MyPlayer::plySpeed - additionalSpeed;
        }
    }
    if(::GetAsyncKeyState('S') & 0x8000)
    {
        //the same
        b_isPlayerStart = true;
        d = 1;
        bool b_isCollideMap = MyGlobal::boolMap[(y + MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + MyPlayer::plySpeed + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = MARSHSPEED;

        if (y + MyPlayer::plySpeed - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 1)
        {
            p.drawImage(x, y + MyPlayer::plySpeed - additionalSpeed, MyPlayer::imgTankDown);
            y += MyPlayer::plySpeed - additionalSpeed;
        }
    }
    if(::GetAsyncKeyState('A') & 0x8000)
    {
        //the same
        b_isPlayerStart = true;
        d = 2;
        bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = MARSHSPEED;

        if (x - MyPlayer::plySpeed + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 2)
        {
            p.drawImage(x - MyPlayer::plySpeed + additionalSpeed, y, MyPlayer::imgTankLeft);
            x -= MyPlayer::plySpeed - additionalSpeed;
        }
    }
    if(::GetAsyncKeyState('D') & 0x8000)
    {
        //the same
        b_isPlayerStart = true;
        d = 3;
        bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = MARSHSPEED;

        if (x + MyPlayer::plySpeed - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 3)
        {
            p.drawImage(x + MyPlayer::plySpeed - additionalSpeed, y, MyPlayer::imgTankRight);
            x += MyPlayer::plySpeed - additionalSpeed;
        }
    }
}

void DisplayWindow::MoveTank2P(QPainter &p)
{
    //load tank img
    /*
    QImage imgTank7Up("tank7up.png");
    QImage imgTank7Down("tank7down.png");
    QImage imgTank7Left("tank7left.png");
    QImage imgTank7Right("tank7right.png");
    QImage imgHealth("life.png");
    */

    //paint current pos&dir
    int &x = MyPlayer::ply2X;
    int &y = MyPlayer::ply2Y;
    int &d = MyPlayer::ply2D;

    //blood display
    double percent = MyPlayer::ply2Hlt/MyPlayer::plyMaxHlt;
    QRectF target(x, y - 8, percent*PICWIDTH, 8);
    p.drawImage(target, MyGlobal::img2PHlt);

    switch (d)
    {
        case 0:p.drawImage(x, y, MyPlayer::imgTankUp); break;
        case 1:p.drawImage(x, y, MyPlayer::imgTankDown); break;
        case 2:p.drawImage(x, y, MyPlayer::imgTankLeft); break;
        case 3:p.drawImage(x, y, MyPlayer::imgTankRight); break;
    }

    int n_isCollide = Is2PCollide(x, y, cntEnemy);

    //react keyPessEvent
    if(::GetAsyncKeyState(VK_UP) & 0x8000)
    {
        //the same
        b_isPlayer2Start = true;
        d = 0;
        bool b_isCollideMap = MyGlobal::boolMap[(y - MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - MyPlayer::plySpeed + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y - MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - MyPlayer::plySpeed + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = MARSHSPEED;

        if (y - MyPlayer::plySpeed + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 0)
        {
            p.drawImage(x, y - MyPlayer::plySpeed + additionalSpeed, MyPlayer::imgTankUp);
            y -= MyPlayer::plySpeed - additionalSpeed;
        }
    }
    if(::GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        //the same
        b_isPlayer2Start = true;
        d = 1;
        bool b_isCollideMap = MyGlobal::boolMap[(y + MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + MyPlayer::plySpeed + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + MyPlayer::plySpeed + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + MyPlayer::plySpeed + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = MARSHSPEED;

        if (y + MyPlayer::plySpeed - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 1)
        {
            p.drawImage(x, y + MyPlayer::plySpeed - additionalSpeed, MyPlayer::imgTankDown);
            y += MyPlayer::plySpeed - additionalSpeed;
        }
    }
    if(::GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        //the same
        b_isPlayer2Start = true;
        d = 2;
        bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = MARSHSPEED;

        if (x - MyPlayer::plySpeed + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 2)
        {
            p.drawImage(x - MyPlayer::plySpeed + additionalSpeed, y, MyPlayer::imgTankLeft);
            x -= MyPlayer::plySpeed - additionalSpeed;
        }
    }
    if(::GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        //the same
        b_isPlayer2Start = true;
        d = 3;
        bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + MyPlayer::plySpeed + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = MARSHSPEED;

        if (x + MyPlayer::plySpeed - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 3)
        {
            p.drawImage(x + MyPlayer::plySpeed - additionalSpeed, y, MyPlayer::imgTankRight);
            x += MyPlayer::plySpeed - additionalSpeed;
        }
    }
}

void DisplayWindow::PlayerAtk()
{
    //has player started
    if (!b_isPlayerStart)
        return ;

    //get pos&dir
    int x = MyPlayer::plyX;
    int y = MyPlayer::plyY;
    int d = MyPlayer::plyD;

    //shoot
    switch (d)
    {
        case 0:
            x = x + PICWIDTH/2 - BULLETWIDTH/2;
            y = y - BULLETHEIGHT;
            break;
        case 1:
            x = x + PICWIDTH/2 - BULLETWIDTH/2;
            y = y + PICHEIGHT;
            break;
        case 2:
            x = x - BULLETHEIGHT;
            y = y + PICHEIGHT/2 - BULLETWIDTH/2;
            break;
        case 3:
            x = x + PICWIDTH;
            y = y + PICHEIGHT/2 - BULLETWIDTH/2;
            break;
    }

    a_Bullets[cntBullets].m_bulletForm = 0;
    a_Bullets[cntBullets].SetX(x);
    a_Bullets[cntBullets].SetY(y);
    a_Bullets[cntBullets].SetDir(d);
    a_Bullets[cntBullets].SetCreator(-1);
    cntBullets++;
}

void DisplayWindow::Player2Atk()
{
    //the same
    if (!b_isPlayer2Start)
        return ;

    int x = MyPlayer::ply2X;
    int y = MyPlayer::ply2Y;
    int d = MyPlayer::ply2D;

    //shoot
    switch (d)
    {
        case 0:
            x = x + PICWIDTH/2 - BULLETWIDTH/2;
            y = y - BULLETHEIGHT;
            break;
        case 1:
            x = x + PICWIDTH/2 - BULLETWIDTH/2;
            y = y + PICHEIGHT;
            break;
        case 2:
            x = x - BULLETHEIGHT;
            y = y + PICHEIGHT/2 - BULLETWIDTH/2;
            break;
        case 3:
            x = x + PICWIDTH;
            y = y + PICHEIGHT/2 - BULLETWIDTH/2;
            break;
    }

    a_Bullets[cntBullets].m_bulletForm = 1;
    a_Bullets[cntBullets].SetX(x);
    a_Bullets[cntBullets].SetY(y);
    a_Bullets[cntBullets].SetDir(d);
    a_Bullets[cntBullets].SetCreator(-2);
    cntBullets++;
}

void DisplayWindow::EnemyCreate()
{
    if (MyFactory::ftrHlt <= 0)
        return ;
    //time ctrl
    QDateTime Now = QDateTime::currentDateTime();

    if (cntEnemy >= 10) {
        NextSpawnTime=Now.addSecs(1+rand()%3);
        return ;
    }


    if (Now<NextSpawnTime) return ;

    NextSpawnTime=Now.addSecs(6+rand()%6);

    //load tankImg
    QImage imgTank1Up("etank1up.png");
    QImage imgTank1Down("etank1down.png");
    QImage imgTank1Left("etank1left.png");
    QImage imgTank1Right("etank1right.png");

    QImage imgTank2Up("etank2up.png");
    QImage imgTank2Down("etank2down.png");
    QImage imgTank2Left("etank2left.png");
    QImage imgTank2Right("etank2right.png");

    //randomly create
    int cd = rand()%4;
    int fx = MyFactory::ftrX, fy = MyFactory::ftrY;
    int x = fx, y = fy - CELLHEIGHT;
    int i = y/CELLHEIGHT, j = x/CELLWIDTH;
    if (!MyGlobal::boolMap[i][j])
    {
        x = fx;
        y = fy + CELLHEIGHT;
    }
    if (!MyGlobal::boolMap[i][j])
    {
        x = fx - CELLWIDTH;
        y = fy;
    }
    if (!MyGlobal::boolMap[i][j])
    {
        x = fx + CELLWIDTH;
        y = fy;
    }

    a_EnemyTank[cntEnemy].SetX(x);
    a_EnemyTank[cntEnemy].SetY(y);
    a_EnemyTank[cntEnemy].SetDir(cd);
    int ran = rand()%100;
    //5%生成boss
    if (ran < 5)
    {
        a_EnemyTank[cntEnemy].SetAtk(ENEMYATK + 10);
        a_EnemyTank[cntEnemy].SetDef(ENEMYDEF + 10);
        a_EnemyTank[cntEnemy].SetHlt(ENEMYLIFE + 100);
        a_EnemyTank[cntEnemy].SetMaxHlt(ENEMYLIFE + 100);
        a_EnemyTank[cntEnemy].imgTankUp = imgTank1Up;
        a_EnemyTank[cntEnemy].imgTankDown = imgTank1Down;
        a_EnemyTank[cntEnemy].imgTankLeft = imgTank1Left;
        a_EnemyTank[cntEnemy].imgTankRight = imgTank1Right;
        a_EnemyTank[cntEnemy].tankType = 2;
    }
    else
    {
        a_EnemyTank[cntEnemy].SetAtk(ENEMYATK);
        a_EnemyTank[cntEnemy].SetDef(ENEMYDEF);
        a_EnemyTank[cntEnemy].SetHlt(ENEMYLIFE);
        a_EnemyTank[cntEnemy].SetMaxHlt(ENEMYLIFE);
        a_EnemyTank[cntEnemy].imgTankUp = imgTank2Up;
        a_EnemyTank[cntEnemy].imgTankDown = imgTank2Down;
        a_EnemyTank[cntEnemy].imgTankLeft = imgTank2Left;
        a_EnemyTank[cntEnemy].imgTankRight = imgTank2Right;
        a_EnemyTank[cntEnemy].tankType = 1;
    }

    cntEnemy++;
}

inline void DeleteTank(MyEnemy* ae, int index, int &cnt)
{
    //delete a tank
    for (int i = index; i < cnt - 1; i++)
    {
        int x = ae[i + 1].GetX();
        int y = ae[i + 1].GetY();
        int d = ae[i + 1].GetDir();
        double hlt = ae[i + 1].GetHlt();
        double maxhlt = ae[i + 1].GetMaxHlt();
        double atk = ae[i + 1].GetAtk();
        double def = ae[i + 1].GetDef();


        ae[i].tankType = ae[i + 1].tankType;
        ae[i].imgTankUp = ae[i + 1].imgTankUp;
        ae[i].imgTankDown = ae[i + 1].imgTankDown;
        ae[i].imgTankLeft = ae[i + 1].imgTankLeft;
        ae[i].imgTankRight = ae[i + 1].imgTankRight;
        ae[i].SetX(x);
        ae[i].SetY(y);
        ae[i].SetDir(d);
        ae[i].SetHlt(hlt);
        ae[i].SetMaxHlt(maxhlt);
        ae[i].SetAtk(atk);
        ae[i].SetDef(def);
    }
    cnt--;
}

void DisplayWindow::MoveEnemyTank(QPainter &p)
{
    //display boom time
    for (int i = 0; i < cntKill; i++)
    {
        int x = s_boomPos[i].x;
        int y = s_boomPos[i].y;
        int t = s_boomPos[i].time;
        bool isBoom = s_boomPos[i].b_isBoom;
        int cut = QTime::currentTime().msec();
        if (abs(cut - t) < 500 && isBoom)
            p.drawImage(x, y, MyGlobal::imgTankBoom);
        else
            s_boomPos[i].b_isBoom = false;
    }

    //random AI
    qsrand(time(NULL));

    for (int i = 0; i < cntEnemy; i++)
    {
        //load img
        QImage imgTankUp = a_EnemyTank[i].imgTankUp;
        QImage imgTankDown = a_EnemyTank[i].imgTankDown;
        QImage imgTankLeft = a_EnemyTank[i].imgTankLeft;
        QImage imgTankRight = a_EnemyTank[i].imgTankRight;

        //get parameter
        int x = a_EnemyTank[i].GetX();
        int y = a_EnemyTank[i].GetY();
        int d = a_EnemyTank[i].GetDir();

        //blood display
        double percent = a_EnemyTank[i].GetHlt()/a_EnemyTank[i].GetMaxHlt();
        QRectF target(x, y - 8, percent*PICWIDTH, 8);
        if (a_EnemyTank[i].tankType == 1)
            p.drawImage(target, MyGlobal::imgEnemyHlt);
        else
            p.drawImage(target, MyGlobal::imgBossHlt);

        switch (d)
        {
            case 0:p.drawImage(x, y, imgTankUp); break;
            case 1:p.drawImage(x, y, imgTankDown); break;
            case 2:p.drawImage(x, y, imgTankLeft); break;
            case 3:p.drawImage(x, y, imgTankRight); break;
        }

        //set boom
        if (a_EnemyTank[i].GetHlt() <= 0)
        {
            int ii = y/CELLHEIGHT, jj = x/CELLWIDTH;
            int ran = rand()%100;
            //set kill award&find a set pos
            if (MyGlobal::boolMap[ii][jj])
                //%5 blood
                if (ran < 5)
                    MyGlobal::objMap[ii][jj] = 1;
                else
                    if (ran < 50)
                        MyGlobal::objMap[ii][jj] = 2;
            else if (MyGlobal::boolMap[ii + 1][jj])
                if (ran < 5)
                    MyGlobal::objMap[ii][jj] = 1;
                else
                    if (ran < 50)
                        MyGlobal::objMap[ii][jj] = 2;
            else if (MyGlobal::boolMap[ii][jj + 1])
                if (ran < 5)
                    MyGlobal::objMap[ii][jj] = 1;
                else
                    if (ran < 50)
                        MyGlobal::objMap[ii][jj] = 2;
            else if (MyGlobal::boolMap[ii - 1][jj])
                if (ran < 5)
                    MyGlobal::objMap[ii][jj] = 1;
                else
                    if (ran < 50)
                        MyGlobal::objMap[ii][jj] = 2;
            else if (MyGlobal::boolMap[ii][jj - 1])
                if (ran < 5)
                    MyGlobal::objMap[ii][jj] = 1;
                else
                    if (ran < 50)
                        MyGlobal::objMap[ii][jj] = 2;

            //delete tank
            DeleteTank(a_EnemyTank, i, cntEnemy);
            cntKill++;

            p.drawImage(x, y, MyGlobal::imgTankBoom);
            s_boomPos[cntKill-1].x = x;
            s_boomPos[cntKill-1].y = y;
            s_boomPos[cntKill-1].time = QTime::currentTime().msec();
            s_boomPos[cntKill-1].b_isBoom = true;
            i--;
            continue;
        }

        int ran = rand()%10000;
        if (ran < 3000)
        {
            d = rand()%4;
            a_EnemyTank[i].SetDir(d);
        }

        int n_isCollide = IsEnemyCollide(x, y, i, cntEnemy);
        if (d == 0)
        {
            //the same
            bool b_isCollideMap = MyGlobal::boolMap[(y - ENEMYSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y - ENEMYSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y - ENEMYSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y - ENEMYSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

            bool b_isOnMarsh = (MyGlobal::logicMap[(y - ENEMYSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y - ENEMYSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y - ENEMYSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y - ENEMYSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

            int additionalSpeed = 0;
            if (b_isOnMarsh)
                additionalSpeed = MARSHSPEED;

            if (y - ENEMYSPEED + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 0)
            {
                p.drawImage(x, y - ENEMYSPEED + additionalSpeed, imgTankUp);
                y -= ENEMYSPEED - additionalSpeed;
                a_EnemyTank[i].SetY(y);
            }
            if (n_isCollide == 0 || y - ENEMYSPEED + additionalSpeed < 0 || !b_isCollideMap)
                a_EnemyTank[i].SetDir(1);
        }
        if (d == 1)
        {
            //the same
            bool b_isCollideMap = MyGlobal::boolMap[(y + ENEMYSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + ENEMYSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + ENEMYSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + ENEMYSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

            bool b_isOnMarsh = (MyGlobal::logicMap[(y + ENEMYSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + ENEMYSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + ENEMYSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + ENEMYSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

            int additionalSpeed = 0;
            if (b_isOnMarsh)
                additionalSpeed = MARSHSPEED;

            if (y + ENEMYSPEED - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 1)
            {
                p.drawImage(x, y + ENEMYSPEED - additionalSpeed, imgTankDown);
                y += ENEMYSPEED - additionalSpeed;
                a_EnemyTank[i].SetY(y);
            }
            if (n_isCollide == 1 || y + ENEMYSPEED - additionalSpeed > 992 || !b_isCollideMap)
                a_EnemyTank[i].SetDir(0);
        }
        if (d == 2)
        {
            //the same
            bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

            bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

            int additionalSpeed = 0;
            if (b_isOnMarsh)
                additionalSpeed = MARSHSPEED;

            if (x - ENEMYSPEED + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 2)
            {
                p.drawImage(x - ENEMYSPEED + additionalSpeed, y, imgTankLeft);
                x -= ENEMYSPEED - additionalSpeed;
                a_EnemyTank[i].SetX(x);
            }
            if (n_isCollide == 2 || x - ENEMYSPEED + additionalSpeed < 0 || !b_isCollideMap)
                a_EnemyTank[i].SetDir(3);
        }
        if (d == 3)
        {
            //the same
            d = 3;
            bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + ENEMYSPEED + COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + ENEMYSPEED + COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + ENEMYSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                    MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + ENEMYSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

            bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + ENEMYSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + ENEMYSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - ENEMYSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                    (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + ENEMYSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

            int additionalSpeed = 0;
            if (b_isOnMarsh)
                additionalSpeed = MARSHSPEED;

            if (x + ENEMYSPEED - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 3)
            {
                p.drawImage(x + ENEMYSPEED - additionalSpeed, y, imgTankRight);
                x += ENEMYSPEED - additionalSpeed;
                a_EnemyTank[i].SetX(x);
            }
            if (n_isCollide == 3 || x + ENEMYSPEED - additionalSpeed > 992 || !b_isCollideMap)
                a_EnemyTank[i].SetDir(2);
        }
    }
}

void DisplayWindow::EnemyAtk()
{
    //the same as player atk
    for (int i = 0; i < cntEnemy; i++)
    {
        int x = a_EnemyTank[i].GetX();
        int y = a_EnemyTank[i].GetY();
        int d = a_EnemyTank[i].GetDir();

        //shoot
        switch (d)
        {
            case 0:
                x = x + PICWIDTH/2 - BULLETWIDTH/2;
                y = y - BULLETHEIGHT;
                break;
            case 1:
                x = x + PICWIDTH/2 - BULLETWIDTH/2;
                y = y + PICHEIGHT;
                break;
            case 2:
                x = x - BULLETHEIGHT;
                y = y + PICHEIGHT/2 - BULLETWIDTH/2;
                break;
            case 3:
                x = x + PICWIDTH;
                y = y + PICHEIGHT/2 - BULLETWIDTH/2;
                break;
        }

        if (a_EnemyTank[i].tankType == 2)
            a_Bullets[cntBullets].m_bulletForm = 3;
        else
            a_Bullets[cntBullets].m_bulletForm = 2;

        a_Bullets[cntBullets].SetX(x);
        a_Bullets[cntBullets].SetY(y);
        a_Bullets[cntBullets].SetDir(d);
        a_Bullets[cntBullets].SetCreator(i);
        cntBullets++;
    }
}

inline int IsCollide(int x, int y, int &cnt)
{
    //is get blood
    int j = (x + PICWIDTH/2)/32, i = (y + PICHEIGHT/2)/32;
    if (MyGlobal::objMap[i][j] == 1)
    {
       MyPlayer::plyHlt += BLOOD;
       if (MyPlayer::plyHlt > MyPlayer::plyMaxHlt)
           MyPlayer::plyHlt = MyPlayer::plyMaxHlt;

       MyGlobal::objMap[i][j] = 0;
    }

    //is get coin
    if (MyGlobal::objMap[i][j] == 2)
    {
       MyPlayer::plyMoney++;
       MyGlobal::objMap[i][j] = 0;
    }

    //is collide other tank
    for (int i = 0; i < cnt; i++)
    {
        if (a_EnemyTank[i].IsDisappear())
            continue;

        int xE = a_EnemyTank[i].GetX();
        int yE = a_EnemyTank[i].GetY();

        int playerMidX = x + PICWIDTH/2, playerMidY = y + PICHEIGHT/2;
        int enemyMidX = xE + PICWIDTH/2, enemyMidY = yE + PICHEIGHT/2;
        double dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

        if (abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
        {
            if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
                return 0;//enemy is in front of player
            if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
                return 1;//enemy is behind  player
            if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
                return 2;//enemy is left to player
            if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
                return 3;//enemy is right to player
        }
    }

    //is collide 2P
    if (DisplayWindow::b_isTPM)
    {
        int xE = MyPlayer::ply2X;
        int yE = MyPlayer::ply2Y;

        int playerMidX = x + PICWIDTH/2, playerMidY = y + PICHEIGHT/2;
        int enemyMidX = xE + PICWIDTH/2, enemyMidY = yE + PICHEIGHT/2;
        double dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

        if (abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
        {
            if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
                return 0;//2p is in front of player
            if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
                return 1;//2p is behind  player
            if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
                return 2;//2p is left to player
            if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
                return 3;//2p is right to player
        }
    }

    //is coliide factory
    int xE = MyFactory::ftrX;
    int yE = MyFactory::ftrY;

    int playerMidX = x + PICWIDTH/2, playerMidY = y + PICHEIGHT/2;
    int enemyMidX = xE + PICWIDTH/2, enemyMidY = yE + PICHEIGHT/2;
    double dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

    if (MyFactory::ftrHlt > 0 && abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
    {
        if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
            return 0;//factory is in front of player
        if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
            return 1;//factory is behind  player
        if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
            return 2;//factory is left to player
        if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
            return 3;//factory is right to player
    }

    return -1;
}

inline int Is2PCollide(int x, int y, int &cnt)
{
    //is get blood
    int j = (x + PICWIDTH/2)/32, i = (y + PICHEIGHT/2)/32;
    if (MyGlobal::objMap[i][j] == 1)
    {
       MyPlayer::ply2Hlt += BLOOD;
       if (MyPlayer::ply2Hlt > MyPlayer::plyMaxHlt)
           MyPlayer::ply2Hlt = MyPlayer::plyMaxHlt;

       MyGlobal::objMap[i][j] = 0;
    }

    //is get coin
    if (MyGlobal::objMap[i][j] == 2)
    {
       MyPlayer::ply2Money++;
       MyGlobal::objMap[i][j] = 0;
    }

    //is collide enemy tank
    for (int i = 0; i < cnt; i++)
    {
        if (a_EnemyTank[i].IsDisappear())
            continue;

        int xE = a_EnemyTank[i].GetX();
        int yE = a_EnemyTank[i].GetY();

        int playerMidX = x + PICWIDTH/2, playerMidY = y + PICHEIGHT/2;
        int enemyMidX = xE + PICWIDTH/2, enemyMidY = yE + PICHEIGHT/2;
        double dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

        if (abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
        {
            if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
                return 0;//enemy is in front of player2
            if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
                return 1;//enemy is behind  player2
            if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
                return 2;//enemy is left to player2
            if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
                return 3;//enemy is right to player2
        }
    }

    //is coliide player1
    int xE = MyPlayer::plyX;
    int yE = MyPlayer::plyY;

    int playerMidX = x + PICWIDTH/2, playerMidY = y + PICHEIGHT/2;
    int enemyMidX = xE + PICWIDTH/2, enemyMidY = yE + PICHEIGHT/2;
    double dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

    if (abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
    {
        if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
            return 0;//1p is in front of 2p
        if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
            return 1;//1p is behind  2p
        if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
            return 2;//1p is left to 2p
        if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
            return 3;//1p is right to 2p
    }

    //is coliide factory
    xE = MyFactory::ftrX;
    yE = MyFactory::ftrY;

    playerMidX = x + PICWIDTH/2; playerMidY = y + PICHEIGHT/2;
    enemyMidX = xE + PICWIDTH/2; enemyMidY = yE + PICHEIGHT/2;
    dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

    if (MyFactory::ftrHlt > 0 && abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
    {
        if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
            return 0;//factory is in front of 2p
        if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
            return 1;//factory is behind  2p
        if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
            return 2;//factory is left to 2p
        if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
            return 3;//factory is right to 2p
    }

    return -1;
}

inline int IsEnemyCollide(int x, int y, int index, int &cnt)
{
    //is enemy collide other enemy
    for (int i = 0; i < cnt; i++)
    {
        if (i == index)
            continue;

        int xE = a_EnemyTank[i].GetX();
        int yE = a_EnemyTank[i].GetY();

        int playerMidX = x + PICWIDTH/2, playerMidY = y + PICHEIGHT/2;
        int enemyMidX = xE + PICWIDTH/2, enemyMidY = yE + PICHEIGHT/2;
        double dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

        if (abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
        {
            if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
                return 0;//other tank is in front of this tank
            if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
                return 1;//other tank is behind  this tank
            if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
                return 2;//other tank is left to this tank
            if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
                return 3;//other tank is right to this tank
        }
    }

    //is enenmy collide player
    int xE = MyPlayer::plyX;
    int yE = MyPlayer::plyY;

    int playerMidX = x + PICWIDTH/2, playerMidY = y + PICHEIGHT/2;
    int enemyMidX = xE + PICWIDTH/2, enemyMidY = yE + PICHEIGHT/2;
    double dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

    if (abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
    {
        if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
            return 0;//player is in front of this tank
        if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
            return 1;//player is behind this tank
        if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
            return 2;//player is left to this tank
        if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
            return 3;//player is right to this tank
    }

    //is enenmy collide factory
    xE = MyFactory::ftrX;
    yE = MyFactory::ftrY;

    playerMidX = x + PICWIDTH/2; playerMidY = y + PICHEIGHT/2;
    enemyMidX = xE + PICWIDTH/2; enemyMidY = yE + PICHEIGHT/2;
    dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

    if (MyFactory::ftrHlt > 0 && abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
    {
        if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
            return 0;//factory is in front of this tank
        if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
            return 1;//factory is behind this tank
        if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
            return 2;//factory is left to this tank
        if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
            return 3;//factory is right to this tank
    }

    //is enemy collide 2p
    if (DisplayWindow::b_isTPM)
    {
        int xE = MyPlayer::ply2X;
        int yE = MyPlayer::ply2Y;

        int playerMidX = x + PICWIDTH/2, playerMidY = y + PICHEIGHT/2;
        int enemyMidX = xE + PICWIDTH/2, enemyMidY = yE + PICHEIGHT/2;
        double dir = (enemyMidX == playerMidX) ? 100.0 : (enemyMidY - playerMidY)*1.0/(enemyMidX - playerMidX);

        if (abs(playerMidX - enemyMidX) <= PICWIDTH && abs(playerMidY - enemyMidY) <= PICHEIGHT)
        {
            if (enemyMidY < playerMidY && (dir > 1 || dir < -1))
                return 0;//2p is in front of this tank
            if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
                return 1;//2p is behind this tank
            if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
                return 2;//2p is left to this tank
            if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
                return 3;//2p is right to this tank
        }
    }

    return -1;
}

inline void DeleteBullets(MyBullet *a, int index, int &cnt)
{
    //delete a bullet
    for (int i = index; i < cnt - 1; i++)
    {
        int x = a[i + 1].GetX();
        int y = a[i + 1].GetY();
        int d = a[i + 1].GetDir();
        int c = a[i + 1].GetCreator();

        a[i].m_bulletForm = a[i + 1].m_bulletForm;
        a[i].SetX(x);
        a[i].SetY(y);
        a[i].SetDir(d);
        a[i].SetCreator(c);
    }
    cnt--;
}

inline bool IsOutofRange(int x, int y, int d, int creator, int &cnt)
{
    switch (d)
    {
            //up
        case 0:
            x = x + BULLETWIDTH/2;
            break;
            //down
        case 1:
            x = x + BULLETWIDTH/2;
            y = y + BULLETHEIGHT;
            break;
            //left
        case 2:
            y = y + BULLETWIDTH/2;
            break;
            //right
        case 3:
            x = x + BULLETHEIGHT;
            y = y + BULLETWIDTH/2;
            break;
    }

    //is bullet out of map or collide rock
    bool ans = x <= 0 || x >= 1024 || y <= 0 || y >= 1024 || !MyGlobal::boolMap[y/CELLHEIGHT][x/CELLWIDTH];
    if (ans)
        return true;
    else
    {
        //is bullet collide enemy tank
        for (int i = 0; i < cnt; i++)
        {
            if (a_EnemyTank[i].IsDisappear())
                continue;

            if (creator == i)
                continue;
            int xE = a_EnemyTank[i].GetX();
            int yE = a_EnemyTank[i].GetY();

            if ((x >= xE && x <= xE + PICWIDTH) && (y >= yE && y <= yE + PICHEIGHT))
            {
                if (creator < 0)
                {
                    double hlt = a_EnemyTank[i].GetHlt();
                    a_EnemyTank[i].SetHlt(hlt - MyPlayer::plyAtk + ENEMYDEF);
                }

                if (DisplayWindow::b_isTPM && creator == -2 && a_EnemyTank[i].GetHlt() <= 0)
                    cntKill2p++;

                return true;
            }
        }
    }

    //is bullet collide factory
    int xP = MyFactory::ftrX;
    int yP = MyFactory::ftrY;
    if (MyFactory::ftrHlt > 0 && (x >= xP && x <= xP + PICWIDTH) && (y >= yP && y <= yP + PICHEIGHT))
    {
        double atk = 0.0;
        if (creator == -1)
            atk = MyPlayer::plyAtk;
        if (creator == -2)
            atk = MyPlayer::ply2Atk;

        MyFactory::ftrHlt = MyFactory::ftrHlt - atk;
        if (creator == -1 && MyFactory::ftrHlt <= 0)
            flagwin = 0;
        if (creator == -2 && MyFactory::ftrHlt <= 0)
            flagwin = 1;

        return true;
    }

    //is bullet collide player's tank
    if (creator != -1)
    {
        int xP = MyPlayer::plyX;
        int yP = MyPlayer::plyY;
        if ((x >= xP && x <= xP + PICWIDTH) && (y >= yP && y <= yP + PICHEIGHT))
        {
            MyPlayer::plyHlt = MyPlayer::plyHlt - ENEMYATK + MyPlayer::plyDef;
            return true;
        }
    }

    //is bullet collide 2p's tank
    if (DisplayWindow::b_isTPM && creator != -2)
    {
        int xP = MyPlayer::ply2X;
        int yP = MyPlayer::ply2Y;
        if ((x + BULLETWIDTH/2 >= xP && x <= xP + PICWIDTH) && (y >= yP && y <= yP + PICHEIGHT))
        {
            MyPlayer::ply2Hlt = MyPlayer::ply2Hlt - ENEMYATK + MyPlayer::plyDef;
            return true;
        }
    }

    return false;
}

void DisplayWindow::MoveBullet(QPainter &p)
{
    //load bullet img
    for (int i = 0; i < cntBullets; i++)
    {
        int x = a_Bullets[i].GetX();
        int y = a_Bullets[i].GetY();
        int c = a_Bullets[i].GetCreator();
        int d = a_Bullets[i].GetDir();

        //is bullet supposed to be deleted
        if (IsOutofRange(x, y, d, c, cntEnemy))
        {
            DeleteBullets(a_Bullets, i, cntBullets);
            i--;
        }
    }

    //move bullets
    for (int i = 0; i < cntBullets; i++)
    {
        QImage imgBulletUp;
        QImage imgBulletDown;
        QImage imgBulletLeft;
        QImage imgBulletRight;

        switch(a_Bullets[i].m_bulletForm)
        {
            case 0:
                imgBulletUp = MyGlobal::imgPlayerBulletUp;
                imgBulletDown = MyGlobal::imgPlayerBulletDown;
                imgBulletLeft = MyGlobal::imgPlayerBulletLeft;
                imgBulletRight = MyGlobal::imgPlayerBulletRight;
                break;
            case 1:
                imgBulletUp = MyGlobal::img2PBulletUp;
                imgBulletDown = MyGlobal::img2PBulletDown;
                imgBulletLeft = MyGlobal::img2PBulletLeft;
                imgBulletRight = MyGlobal::img2PBulletRight;
                break;
            case 2:
                imgBulletUp = MyGlobal::imgEnemyBulletUp;
                imgBulletDown = MyGlobal::imgEnemyBulletDown;
                imgBulletLeft = MyGlobal::imgEnemyBulletLeft;
                imgBulletRight = MyGlobal::imgEnemyBulletRight;
                break;
            case 3:
                imgBulletUp = MyGlobal::imgBossBulletUp;
                imgBulletDown = MyGlobal::imgBossBulletDown;
                imgBulletLeft = MyGlobal::imgBossBulletLeft;
                imgBulletRight = MyGlobal::imgBossBulletRight;
                break;
        }
        int x = a_Bullets[i].GetX();
        int y = a_Bullets[i].GetY();
        int d = a_Bullets[i].GetDir();

        switch (d)
        {
            case 0:
                p.drawImage(x, y - BULLETSPEED, imgBulletUp);
                y -= BULLETSPEED;
                break;
            case 1:
                p.drawImage(x, y + BULLETSPEED, imgBulletDown);
                y += BULLETSPEED;
                break;
            case 2:
                p.drawImage(x - BULLETSPEED, y, imgBulletLeft);
                x -= BULLETSPEED;
                break;
            case 3:
                p.drawImage(x + BULLETSPEED, y, imgBulletRight);
                x += BULLETSPEED;
                break;
        }

        a_Bullets[i].SetX(x);
        a_Bullets[i].SetY(y);
    }
}
void DisplayWindow::closeEvent(QCloseEvent *event){
    emit Exit();
}

