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

int DisplayWindow::keyValue;

MyBullet a_Bullets[10000];
static int cntBullets = 0;

inline void DeleteBullets(MyBullet*, int, int&);
inline bool IsOutofRange(int, int);

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

    //react keyPessEvent
    if (keyValue == 87)
    {
        d = 0;
        if (y - NORMALSPEED >= 0 && MyGlobal::boolMap[(y - NORMALSPEED)/32][x/32])
        {
            p.drawImage(x, y - NORMALSPEED, imgTank1Up);
            y -= NORMALSPEED;
        }
    }
    if (keyValue == 83)
    {
        d = 1;
        if (y + NORMALSPEED <= 992 && MyGlobal::boolMap[(y + NORMALSPEED)/32][x/32])
        {
            p.drawImage(x, y + NORMALSPEED, imgTank1Down);
            y += NORMALSPEED;
        }
    }
    if (keyValue == 65)
    {
        d = 2;
        if (x - NORMALSPEED >= 0 && MyGlobal::boolMap[y/32][(x - NORMALSPEED)/32])
        {
            p.drawImage(x - NORMALSPEED, y, imgTank1Left);
            x -= NORMALSPEED;
        }
    }
    if (keyValue == 68)
    {
        d = 3;
        if (x + NORMALSPEED <= 992 && MyGlobal::boolMap[y/32][(x + NORMALSPEED)/32])
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

        switch (d)
        {
            case 0:keyValue = 87; break;
            case 1:keyValue = 83; break;
            case 2:keyValue = 65; break;
            case 3:keyValue = 68; break;
        }
    }
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
    return ans;
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
