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
#include "myglobal.h"
#include "myplayer.h"
#include "mybullet.h"
#include "myenemy.h"
#define BLOOD 30
#define COLLIDEFIX 4
#define MARSHSPEED 1

int DisplayWindow::keyValue;
bool DisplayWindow::b_isTPM;

struct BoomPos
{
    int x, y;
    bool b_isBoom;
} s_boomPos[1000];

MyBullet a_Bullets[10000];
extern MyEnemy a_EnemyTank[100];

inline void DeleteBullets(MyBullet*, int, int&);
inline bool IsOutofRange(int, int, int);
inline int IsCollide(int, int);
inline int Is2PCollide(int, int);
inline int IsEnemyCollide(int, int, int);

DisplayWindow::DisplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);

    setFocusPolicy(Qt::StrongFocus);

    //qDebug() << isTPM;

    //set fps
    QTimer *new_t = new QTimer(this);
    connect(new_t, SIGNAL(timeout()), this, SLOT(update()));
    new_t->start(4);//240 fps

    //set enemy atk frequency
    QTimer *enemyAtk = new QTimer(this);
    connect(enemyAtk, SIGNAL(timeout()), this, SLOT(EnemyAtk()));
    enemyAtk->start(750);

    //set player atk max frequency
    QTimer *playerAtk = new QTimer(this);
    connect(playerAtk, SIGNAL(timeout()), this, SLOT(PlayerAtk()));
    playerAtk->start(500);

    //set player2 atk max frequency
    if (b_isTPM)
    {
        QTimer *player2Atk = new QTimer(this);
        connect(player2Atk, SIGNAL(timeout()), this, SLOT(Player2Atk()));
        player2Atk->start(500);
    }
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    //display parameter
    ui->lbl_health->setNum(MyPlayer::plyHlt);
    ui->lbl_money->setNum(MyPlayer::plyMoney);
    ui->lbl_killenemy->setNum(MyPlayer::plyKill + ENEMYNUMBER - cntEnemy);

    //QString txtHealth; txtHealth.arg(MyPlayer::plyHlt, 0, 'f', 1);
    //ui->lbl_health->setText(txtHealth);
    //you win game
    if (cntEnemy == 0)
        close();

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
    //W-87
    //S-83
    //A-65
    //D-68
    //J-74
    //K-75
    //L-76
}

void DisplayWindow::PaintMap(QPainter &p)
{
    //load map img
    QImage imgGrass("grass.png");
    QImage imgRock("rock.png");
    QImage imgMarsh("marsh.png");
    QImage imgBlood("blood.png");
    QImage imgCoin("coin.png");

    //paint map
    qsrand(time(NULL));
    for (int i = 0; i < INUM; i++)
        for (int j = 0; j < JNUM; j++)
        {
            char n = MyGlobal::logicMap[i][j];
            int x = j*PICWIDTH, y = i*PICHEIGHT;

            switch (n)
            {
                case 'G':p.drawImage(x, y, imgGrass); break;
                case 'R':p.drawImage(x, y, imgRock); break;
                case 'M':p.drawImage(x, y, imgMarsh); break;
                default:p.drawImage(x, y, imgGrass);
            }

            if (MyGlobal::objMap[i][j] == 1)
                p.drawImage(x, y, imgBlood);
            if (MyGlobal::objMap[i][j] == 2)
                p.drawImage(x, y, imgCoin);

            int ran = rand()%10000000;
            if (ran < 2 && MyGlobal::boolMap[i][j] && MyGlobal::dfsMap[i][j] == MyGlobal::m_TrueBlockMark)
                MyGlobal::objMap[i][j] = 1;
            else
            if (ran < 4 && MyGlobal::boolMap[i][j] && MyGlobal::dfsMap[i][j] == MyGlobal::m_TrueBlockMark)
                MyGlobal::objMap[i][j] = 2;
        }
}

void DisplayWindow::MoveTank(QPainter &p)
{
    //load tank img
    QImage imgTank1Up("tank1up.png");
    QImage imgTank1Down("tank1down.png");
    QImage imgTank1Left("tank1left.png");
    QImage imgTank1Right("tank1right.png");
    QImage imgTankBoom("tankboom.png");

    //paint current pos&dir
    int &x = MyPlayer::plyX;
    int &y = MyPlayer::plyY;
    int &d = MyPlayer::plyD;
    switch (d)
    {
        case 0:p.drawImage(x, y, imgTank1Up); break;
        case 1:p.drawImage(x, y, imgTank1Down); break;
        case 2:p.drawImage(x, y, imgTank1Left); break;
        case 3:p.drawImage(x, y, imgTank1Right); break;
    }

    //is dead
    if (MyPlayer::plyHlt <= 0)
    {
        p.drawImage(x, y, imgTankBoom);
        close();
    }

    int n_isCollide = IsCollide(x, y);

    //react keyPessEvent
    if (keyValue == 87)
    {
        b_isPlayerStart = true;
        d = 0;
        bool b_isCollideMap = MyGlobal::boolMap[(y - NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - NORMALSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y - NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - NORMALSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = 3*MARSHSPEED;

        if (y - NORMALSPEED + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 0)
        {
            p.drawImage(x, y - NORMALSPEED + additionalSpeed, imgTank1Up);
            y -= NORMALSPEED - additionalSpeed;
        }
    }
    if (keyValue == 83)
    {
        b_isPlayerStart = true;
        d = 1;
        bool b_isCollideMap = MyGlobal::boolMap[(y + NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + NORMALSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = 3*MARSHSPEED;

        if (y + NORMALSPEED - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 1)
        {
            p.drawImage(x, y + NORMALSPEED - additionalSpeed, imgTank1Down);
            y += NORMALSPEED - additionalSpeed;
        }
    }
    if (keyValue == 65)
    {
        b_isPlayerStart = true;
        d = 2;
        bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = 3*MARSHSPEED;

        if (x - NORMALSPEED + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 2)
        {
            p.drawImage(x - NORMALSPEED + additionalSpeed, y, imgTank1Left);
            x -= NORMALSPEED - additionalSpeed;
        }
    }
    if (keyValue == 68)
    {
        b_isPlayerStart = true;
        d = 3;
        bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = 3*MARSHSPEED;

        if (x + NORMALSPEED - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 3)
        {
            p.drawImage(x + NORMALSPEED - additionalSpeed, y, imgTank1Right);
            x += NORMALSPEED - additionalSpeed;
        }
    }

    keyValue = NULL;
}

void DisplayWindow::MoveTank2P(QPainter &p)
{
    //load tank img
    QImage imgTank7Up("tank7up.png");
    QImage imgTank7Down("tank7down.png");
    QImage imgTank7Left("tank7left.png");
    QImage imgTank7Right("tank7right.png");
    QImage imgTankBoom("tankboom.png");

    //paint current pos&dir
    int &x = MyPlayer::ply2X;
    int &y = MyPlayer::ply2Y;
    int &d = MyPlayer::ply2D;
    switch (d)
    {
        case 0:p.drawImage(x, y, imgTank7Up); break;
        case 1:p.drawImage(x, y, imgTank7Down); break;
        case 2:p.drawImage(x, y, imgTank7Left); break;
        case 3:p.drawImage(x, y, imgTank7Right); break;
    }

    //is dead
    if (MyPlayer::ply2Hlt <= 0)
    {
        p.drawImage(x, y, imgTankBoom);
        close();
    }

    int n_isCollide = Is2PCollide(x, y);

    //react keyPessEvent
    if (keyValue == 16777235)
    {
        b_isPlayer2Start = true;
        d = 0;
        bool b_isCollideMap = MyGlobal::boolMap[(y - NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y - NORMALSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y - NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y - NORMALSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = 3*MARSHSPEED;

        if (y - NORMALSPEED + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 0)
        {
            p.drawImage(x, y - NORMALSPEED + additionalSpeed, imgTank7Up);
            y -= NORMALSPEED - additionalSpeed;
        }
    }
    if (keyValue == 16777237)
    {
        b_isPlayer2Start = true;
        d = 1;
        bool b_isCollideMap = MyGlobal::boolMap[(y + NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + NORMALSPEED + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + NORMALSPEED + COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + NORMALSPEED + PICHEIGHT -COLLIDEFIX)/CELLHEIGHT][(x + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = 3*MARSHSPEED;

        if (y + NORMALSPEED - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 1)
        {
            p.drawImage(x, y + NORMALSPEED - additionalSpeed, imgTank7Down);
            y += NORMALSPEED - additionalSpeed;
        }
    }
    if (keyValue == 16777234)
    {
        b_isPlayer2Start = true;
        d = 2;
        bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = 3*MARSHSPEED;

        if (x - NORMALSPEED + additionalSpeed >= 0 && b_isCollideMap && n_isCollide != 2)
        {
            p.drawImage(x - NORMALSPEED + additionalSpeed, y, imgTank7Left);
            x -= NORMALSPEED - additionalSpeed;
        }
    }
    if (keyValue == 16777236)
    {
        b_isPlayer2Start = true;
        d = 3;
        bool b_isCollideMap = MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] &&
                MyGlobal::boolMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH];

        bool b_isOnMarsh = (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + COLLIDEFIX)/CELLHEIGHT][(x - NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M') ||
                (MyGlobal::logicMap[(y + PICHEIGHT - COLLIDEFIX)/CELLHEIGHT][(x + NORMALSPEED + PICWIDTH - COLLIDEFIX)/CELLWIDTH] == 'M');

        int additionalSpeed = 0;
        if (b_isOnMarsh)
            additionalSpeed = 3*MARSHSPEED;

        if (x + NORMALSPEED - additionalSpeed <= 992 && b_isCollideMap && n_isCollide != 3)
        {
            p.drawImage(x + NORMALSPEED - additionalSpeed, y, imgTank7Right);
            x += NORMALSPEED - additionalSpeed;
        }
    }

    keyValue = NULL;
}

void DisplayWindow::PlayerAtk()
{
    if (!b_isPlayerStart)
        return ;

    int &x = MyPlayer::plyX;
    int &y = MyPlayer::plyY;
    int &d = MyPlayer::plyD;

    a_Bullets[cntBullets].SetX(x);
    a_Bullets[cntBullets].SetY(y);
    a_Bullets[cntBullets].SetDir(d);
    a_Bullets[cntBullets].SetCreator(-1);
    cntBullets++;
}

void DisplayWindow::Player2Atk()
{
    if (!b_isPlayer2Start)
        return ;

    int &x = MyPlayer::ply2X;
    int &y = MyPlayer::ply2Y;
    int &d = MyPlayer::ply2D;

    a_Bullets[cntBullets].SetX(x);
    a_Bullets[cntBullets].SetY(y);
    a_Bullets[cntBullets].SetDir(d);
    a_Bullets[cntBullets].SetCreator(-2);
    cntBullets++;
}

void DisplayWindow::MoveEnemyTank(QPainter &p)
{
    //load tank img
    QImage imgTank6Up("tank6up.png");
    QImage imgTank6Down("tank6down.png");
    QImage imgTank6Left("tank6left.png");
    QImage imgTank6Right("tank6right.png");
    QImage imgTankBoom("tankboom.png");

    //set boom time------------------------------------------------bugs
    for (int i = 0; i < ENEMYNUMBER-cntEnemy; i++)
    {
        int x = s_boomPos[i].x;
        int y = s_boomPos[i].y;
        bool isBoom = s_boomPos[i].b_isBoom;
        int cut = QTime::currentTime().msec();
        if (cut < 750 && isBoom)
            p.drawImage(x, y, imgTankBoom);
        else
            s_boomPos[i].b_isBoom = false;
    }

    //random AI
    qsrand(time(NULL));

    for (int i = 0; i < ENEMYNUMBER; i++)
    {
        if (a_EnemyTank[i].IsDisappear())
            continue;

        int x = a_EnemyTank[i].GetX();
        int y = a_EnemyTank[i].GetY();
        int d = a_EnemyTank[i].GetDir();

        switch (d)
        {
            case 0:p.drawImage(x, y, imgTank6Up); break;
            case 1:p.drawImage(x, y, imgTank6Down); break;
            case 2:p.drawImage(x, y, imgTank6Left); break;
            case 3:p.drawImage(x, y, imgTank6Right); break;
        }

        if (a_EnemyTank[i].GetHlt() <= 0)
        {
            a_EnemyTank[i].SetDisappear(true);
            cntEnemy--;
            p.drawImage(x, y, imgTankBoom);
            s_boomPos[ENEMYNUMBER-cntEnemy-1].x = x;
            s_boomPos[ENEMYNUMBER-cntEnemy-1].y = y;
            s_boomPos[ENEMYNUMBER-cntEnemy-1].b_isBoom = true;
            continue;
        }

        int ran = rand()%10000;
        if (ran < 3000)
        {
            d = rand()%4;
            a_EnemyTank[i].SetDir(d);
        }

        int n_isCollide = IsEnemyCollide(x, y, i);
        if (d == 0)
        {
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
                p.drawImage(x, y - ENEMYSPEED + additionalSpeed, imgTank6Up);
                y -= ENEMYSPEED - additionalSpeed;
                a_EnemyTank[i].SetY(y);
            }
            if (n_isCollide == 0 || y - ENEMYSPEED + additionalSpeed < 0 || !b_isCollideMap)
                a_EnemyTank[i].SetDir(1);
        }
        if (d == 1)
        {
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
                p.drawImage(x, y + ENEMYSPEED - additionalSpeed, imgTank6Down);
                y += ENEMYSPEED - additionalSpeed;
                a_EnemyTank[i].SetY(y);
            }
            if (n_isCollide == 1 || y + ENEMYSPEED - additionalSpeed > 992 || !b_isCollideMap)
                a_EnemyTank[i].SetDir(0);
        }
        if (d == 2)
        {
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
                p.drawImage(x - ENEMYSPEED + additionalSpeed, y, imgTank6Left);
                x -= ENEMYSPEED - additionalSpeed;
                a_EnemyTank[i].SetX(x);
            }
            if (n_isCollide == 2 || x - ENEMYSPEED + additionalSpeed < 0 || !b_isCollideMap)
                a_EnemyTank[i].SetDir(3);
        }
        if (d == 3)
        {
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
                p.drawImage(x + ENEMYSPEED - additionalSpeed, y, imgTank6Right);
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
    for (int i = 0; i < ENEMYNUMBER; i++)
    {
        if (a_EnemyTank[i].IsDisappear())
            continue;

        int x = a_EnemyTank[i].GetX();
        int y = a_EnemyTank[i].GetY();
        int d = a_EnemyTank[i].GetDir();

        a_Bullets[cntBullets].SetX(x);
        a_Bullets[cntBullets].SetY(y);
        a_Bullets[cntBullets].SetDir(d);
        a_Bullets[cntBullets].SetCreator(i);
        cntBullets++;
    }
}

inline int IsCollide(int x, int y)
{
    //is get blood
    int j = (x + PICWIDTH/2)/32, i = (y + PICHEIGHT/2)/32;
    if (MyGlobal::objMap[i][j] == 1)
    {
       MyPlayer::plyHlt += BLOOD;
       if (MyPlayer::plyHlt > 100)
           MyPlayer::plyHlt = 100.0;

       MyGlobal::objMap[i][j] = 0;
    }

    //is get coin
    if (MyGlobal::objMap[i][j] == 2)
    {
       MyPlayer::plyMoney++;
       MyGlobal::objMap[i][j] = 0;
    }

    //is collide other tank
    for (int i = 0; i < ENEMYNUMBER; i++)
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

    return -1;
}

inline int Is2PCollide(int x, int y)
{
    //is get blood
    int j = (x + PICWIDTH/2)/32, i = (y + PICHEIGHT/2)/32;
    if (MyGlobal::objMap[i][j] == 1)
    {
       MyPlayer::ply2Hlt += BLOOD;
       if (MyPlayer::ply2Hlt > 100)
           MyPlayer::ply2Hlt = 100.0;

       MyGlobal::objMap[i][j] = 0;
    }

    //is get coin
    if (MyGlobal::objMap[i][j] == 2)
    {
       MyPlayer::ply2Money++;
       MyGlobal::objMap[i][j] = 0;
    }

    //is collide other tank
    for (int i = 0; i < ENEMYNUMBER; i++)
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

    return -1;
}

inline int IsEnemyCollide(int x, int y, int index)
{
    for (int i = 0; i < ENEMYNUMBER; i++)
    {
        if (a_EnemyTank[i].IsDisappear())
            continue;

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
                return 0;//enemy is in front of player
            if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
                return 1;//enemy is behind  player
            if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
                return 2;//enemy is left to player
            if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
                return 3;//enemy is right to player
        }
    }

    int xE = MyPlayer::plyX;
    int yE = MyPlayer::plyY;

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
                return 0;//enemy is in front of player2
            if (enemyMidY > playerMidY && (dir > 1 || dir < -1))
                return 1;//enemy is behind  player2
            if (enemyMidX < playerMidX && (dir > -1 && dir < 1))
                return 2;//enemy is left to player2
            if (enemyMidX > playerMidX && (dir > -1 && dir < 1))
                return 3;//enemy is right to player2
        }
    }

    return -1;
}

inline void DeleteBullets(MyBullet *a, int index, int &cnt)
{
    for (int i = index; i < cnt - 1; i++)
    {
        int x = a[i + 1].GetX();
        int y = a[i + 1].GetY();
        int d = a[i + 1].GetDir();
        int c = a[i + 1].GetCreator();

        a[i].SetX(x);
        a[i].SetY(y);
        a[i].SetDir(d);
        a[i].SetCreator(c);
    }
    cnt--;
}

inline bool IsOutofRange(int x, int y, int creator)
{
    bool ans = x <= 0 || x >= 1024 || y <= 0 || y >= 1024 || !MyGlobal::boolMap[(y + BULLETHEIGHT/2)/32][(x + BULLETWIDTH/2)/32];
    if (ans)
        return true;
    else
    {
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (a_EnemyTank[i].IsDisappear())
                continue;

            if (creator == i)
                continue;
            int xE = a_EnemyTank[i].GetX();
            int yE = a_EnemyTank[i].GetY();

            if ((x + BULLETWIDTH/2 >= xE && x + BULLETWIDTH/2 <= xE + PICWIDTH) && (y + BULLETHEIGHT/2 >= yE && y + BULLETHEIGHT/2 <= yE + PICHEIGHT))
            {
                if (creator == -1)
                {
                    double hlt = a_EnemyTank[i].GetHlt();
                    a_EnemyTank[i].SetHlt(hlt - PLAYERATK + ENEMYDEF);
                }
                return true;
            }
        }
    }

    if (creator != -1)
    {
        int xP = MyPlayer::plyX;
        int yP = MyPlayer::plyY;
        if ((x + BULLETWIDTH/2 >= xP && x + BULLETWIDTH/2 <= xP + PICWIDTH) && (y + BULLETHEIGHT/2 >= yP && y + BULLETHEIGHT/2 <= yP + PICHEIGHT))
        {
            MyPlayer::plyHlt = MyPlayer::plyHlt - ENEMYATK + PLAYERDEF;
            return true;
        }

        if (DisplayWindow::b_isTPM && creator != -2)
        {
            int xP = MyPlayer::ply2X;
            int yP = MyPlayer::ply2Y;
            if ((x + BULLETWIDTH/2 >= xP && x + BULLETWIDTH/2 <= xP + PICWIDTH) && (y + BULLETHEIGHT/2 >= yP && y + BULLETHEIGHT/2 <= yP + PICHEIGHT))
            {
                MyPlayer::ply2Hlt = MyPlayer::ply2Hlt - ENEMYATK + PLAYERDEF;
                return true;
            }
        }
    }

    return false;
}

void DisplayWindow::MoveBullet(QPainter &p)
{
    //load bullet img
    QImage imgBullet1("bullet1.png");

    for (int i = 0; i < cntBullets; i++)
    {
        int x = a_Bullets[i].GetX();
        int y = a_Bullets[i].GetY();
        int c = a_Bullets[i].GetCreator();

        if (IsOutofRange(x, y, c))
        {
            DeleteBullets(a_Bullets, i, cntBullets);
            i--;
        }
    }

    for (int i = 0; i < cntBullets; i++)
    {
        int x = a_Bullets[i].GetX();
        int y = a_Bullets[i].GetY();
        int d = a_Bullets[i].GetDir();

        switch (d)
        {
            case 0:
                p.drawImage(x, y - BULLETSPEED, imgBullet1);
                y -= BULLETSPEED;
                break;
            case 1:
                p.drawImage(x, y + BULLETSPEED, imgBullet1);
                y += BULLETSPEED;
                break;
            case 2:
                p.drawImage(x - BULLETSPEED, y, imgBullet1);
                x -= BULLETSPEED;
                break;
            case 3:
                p.drawImage(x + BULLETSPEED, y, imgBullet1);
                x += BULLETSPEED;
                break;
        }

        a_Bullets[i].SetX(x);
        a_Bullets[i].SetY(y);
    }
}

void DisplayWindow::closeEvent(QCloseEvent *event)
{
    int choose;
    if (!DisplayWindow::b_isTPM)
    {
        if (cntEnemy == 0)
        {
            //save
            freopen("save.sav", "w", stdout);
            std::cout << MyPlayer::plyMoney << " " << MyPlayer::plyKill+ENEMYNUMBER - cntEnemy;
            fclose(stdout);

            //win
            choose= QMessageBox::question(this, tr("quit game"),
                                         QString(tr("Game Over, YOU WIN")),
                                         QMessageBox::Yes);
            if (choose== QMessageBox::Yes)
                event->accept();
        }
        else
        if (MyPlayer::plyHlt > 0)
        {
            choose= QMessageBox::question(this, tr("quit game"),
                                         QString(tr("are you sure?")),
                                         QMessageBox::Yes | QMessageBox::No);
            if (choose== QMessageBox::No)
                event->ignore();
            else
            if (choose== QMessageBox::Yes)
            {
                //save
                freopen("save.sav", "w", stdout);
                std::cout << MyPlayer::plyMoney << " " << MyPlayer::plyKill+ENEMYNUMBER - cntEnemy;
                fclose(stdout);

                event->accept();
            }
        }
        else
        {
            //save
            freopen("save.sav", "w", stdout);
            std::cout << MyPlayer::plyMoney << " " << MyPlayer::plyKill+ENEMYNUMBER - cntEnemy;
            fclose(stdout);

            //lost
            choose= QMessageBox::question(this, tr("quit game"),
                                         QString(tr("Game Over, YOU DEAD")),
                                         QMessageBox::Yes);
            if (choose== QMessageBox::Yes)
                event->accept();
        }
    }
    else
    {
        if (MyPlayer::plyHlt <= 0)
        {
            //save
            freopen("save.sav", "w", stdout);
            std::cout << MyPlayer::plyMoney << " " << MyPlayer::plyKill+ENEMYNUMBER - cntEnemy;
            fclose(stdout);

            //win
            choose= QMessageBox::question(this, tr("quit game"),
                                         QString(tr("Game Over, 2P WIN")),
                                         QMessageBox::Yes);
            if (choose== QMessageBox::Yes)
                event->accept();
        }
        else
        if (MyPlayer::plyHlt > 0 && MyPlayer::ply2Hlt > 0)
        {
            choose= QMessageBox::question(this, tr("quit game"),
                                         QString(tr("are you sure?")),
                                         QMessageBox::Yes | QMessageBox::No);
            if (choose== QMessageBox::No)
                event->ignore();
            else
            if (choose== QMessageBox::Yes)
            {
                //save
                freopen("save.sav", "w", stdout);
                std::cout << MyPlayer::plyMoney << " " << MyPlayer::plyKill+ENEMYNUMBER - cntEnemy;
                fclose(stdout);

                event->accept();
            }
        }
        else
        {
            //save
            freopen("save.sav", "w", stdout);
            std::cout << MyPlayer::plyMoney << " " << MyPlayer::plyKill+ENEMYNUMBER - cntEnemy;
            fclose(stdout);

            //lost
            choose= QMessageBox::question(this, tr("quit game"),
                                         QString(tr("Game Over, 1P WIN")),
                                         QMessageBox::Yes);
            if (choose== QMessageBox::Yes)
                event->accept();
        }
    }
}
