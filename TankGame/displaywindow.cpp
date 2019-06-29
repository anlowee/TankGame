#include "displaywindow.h"
#include "ui_displaywindow.h"
#include "mymap.h"
#include <QPainter>
#include <QPixmap>
#include <QStyleOption>
#include <QImage>
#include <QTime>
#include <QKeyEvent>
#include <iostream>
#include <QPropertyAnimation>
#include <QtCore>
#include "myglobal.h"
#include "myplayer.h"
#include "mybullet.h"
#include "myenemy.h"

int DisplayWindow::keyValue;

MyBullet a_Bullets[10000];
static int cntBullets = 0;
static int cntEnemy = ENEMYNUMBER;
extern MyEnemy a_EnemyTank[100];

inline void DeleteBullets(MyBullet*, int, int&);
inline bool IsOutofRange(int, int);
inline int IsCollide(int, int);

DisplayWindow::DisplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);

    setFocusPolicy(Qt::StrongFocus);
    QTimer *new_t = new QTimer(this);
    connect(new_t, SIGNAL(timeout()), this, SLOT(update()));
    new_t->start(4);//240 fps
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    //paint Map
    PaintMap(p);

    //Move Player
    MoveTank(p);

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

    //paint map
    for (int i = 0; i < INUM; i++)
        for (int j = 0; j < JNUM; j++)
        {
            char n = MyGlobal::logicMap[i][j];
            int x = j*PICWIDTH, y = i*PICHEIGHT;

            switch (n)
            {
                case 'G':p.drawImage(x, y, imgGrass); break;
                case 'R':p.drawImage(x, y, imgRock); break;
                default:p.drawImage(x, y, imgGrass);
            }
        }
}

void DisplayWindow::MoveTank(QPainter &p)
{
    //load tank img
    QImage imgTank1Up("tank1up.png");
    QImage imgTank1Down("tank1down.png");
    QImage imgTank1Left("tank1left.png");
    QImage imgTank1Right("tank1right.png");

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

    int n_isCollide = IsCollide(x, y);
    //react keyPessEvent
    if (keyValue == 87)
    {
        d = 0;
        if (y - NORMALSPEED >= 0 && MyGlobal::boolMap[(y - NORMALSPEED)/32][x/32] && n_isCollide != 0)
        {
            p.drawImage(x, y - NORMALSPEED, imgTank1Up);
            y -= NORMALSPEED;
        }
    }
    if (keyValue == 83)
    {
        d = 1;
        if (y + NORMALSPEED <= 992 && MyGlobal::boolMap[(y + NORMALSPEED)/32][x/32] && n_isCollide != 1)
        {
            p.drawImage(x, y + NORMALSPEED, imgTank1Down);
            y += NORMALSPEED;
        }
    }
    if (keyValue == 65)
    {
        d = 2;
        if (x - NORMALSPEED >= 0 && MyGlobal::boolMap[y/32][(x - NORMALSPEED)/32] && n_isCollide != 2)
        {
            p.drawImage(x - NORMALSPEED, y, imgTank1Left);
            x -= NORMALSPEED;
        }
    }
    if (keyValue == 68)
    {
        d = 3;
        if (x + NORMALSPEED <= 992 && MyGlobal::boolMap[y/32][(x + NORMALSPEED)/32] && n_isCollide != 3)
        {
            p.drawImage(x + NORMALSPEED, y, imgTank1Right);
            x += NORMALSPEED;
        }
    }
    if (keyValue == 74)
    {
        a_Bullets[cntBullets].SetX(x);
        a_Bullets[cntBullets].SetY(y);
        a_Bullets[cntBullets].SetDir(d);
        cntBullets++;

        /*
        switch (d)
        {
            case 0:keyValue = 87; break;
            case 1:keyValue = 83; break;
            case 2:keyValue = 65; break;
            case 3:keyValue = 68; break;
        }
        */
    }

    keyValue = NULL;
}

void DisplayWindow::MoveEnemyTank(QPainter &p)
{
    //load tank img
    QImage imgTank6Up("tank6up.png");
    QImage imgTank6Down("tank6down.png");
    QImage imgTank6Left("tank6left.png");
    QImage imgTank6Right("tank6right.png");

    for (int i = 0; i < cntEnemy; i++)
    {
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
    }
}

inline int IsCollide(int x, int y)
{
    for (int i = 0; i < cntEnemy; i++)
    {
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

inline void DeleteBullets(MyBullet *a, int index, int &cnt)
{
    for (int i = index; i < cnt - 1; i++)
    {
        int x = a[i + 1].GetX();
        int y = a[i + 1].GetY();
        int d = a[i + 1].GetDir();
        a[i].SetX(x);
        a[i].SetY(y);
        a[i].SetDir(d);
    }
    cnt--;
}

inline bool IsOutofRange(int x, int y)
{
    bool ans = x <= 0 || x >= 1024 || y <= 0 || y >= 1024 || !MyGlobal::boolMap[y/32][x/32];
    if (ans)
        return true;
    else
    {
        for (int i = 0; i < cntEnemy; i++)
        {
            int xE = a_EnemyTank[i].GetX();
            int yE = a_EnemyTank[i].GetY();

            if ((x + BULLETWIDTH/2 >= xE && x + BULLETWIDTH/2 <= xE + PICWIDTH) && (y + BULLETHEIGHT/2 >= yE && y + BULLETHEIGHT/2 <= yE + PICHEIGHT))
                return true;
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

        if (IsOutofRange(x, y))
        {
            DeleteBullets(a_Bullets, i, cntBullets);
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
