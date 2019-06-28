#include "displaywindow.h"
#include "ui_displaywindow.h"
#include "mymap.h"
#include <QPainter>
#include <QStyleOption>
#include <QImage>
#include <QTime>
#include <QKeyEvent>
#include <iostream>
#include "myglobal.h"
#include "myplayer.h"

int DisplayWindow::keyValue;
int MyPlayer::plyX = 0;
int MyPlayer::plyY = 0;
int MyPlayer::plyD = 1;

DisplayWindow::DisplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow)
{
    setFocusPolicy(Qt::StrongFocus);
    ui->setupUi(this);

    //MyPlayer *new_p = new MyPlayer;
    //qDebug() << "==Press a key";
    //this->grabKeyboard();
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    //Create Map

    //load map img
    QImage imgGrass("grass.png");
    QImage imgRock("rock.png");
    QImage imgSnow("snow.png");
    QImage imgMarsh("marsh.png");
    QImage imgTree("tree.png");
    QImage imgWater("water.png");

    //load tank img
    QImage imgTank1Up("tank1up.png");
    QImage imgTank1Down("tank1down.png");
    QImage imgTank1Left("tank1left.png");
    QImage imgTank1Right("tank1right.png");

    for (int i = 0; i < INUM; i++)
        for (int j = 0; j < JNUM; j++)
        {
            char n = MyGlobal::logicMap[i][j];
            int x = j*PICWIDTH, y = i*PICHEIGHT;

            switch (n)
            {
                case 'G':p.drawImage(x, y, imgGrass); break;
                case 'T':p.drawImage(x, y, imgTree); break;
                case 'S':p.drawImage(x, y, imgSnow); break;
                case 'M':p.drawImage(x, y, imgMarsh); break;
                case 'R':p.drawImage(x, y, imgRock); break;
                case 'W':p.drawImage(x, y, imgWater); break;
                default:p.drawImage(x, y, imgGrass);
            }
        }

    //Display move
    int keyValue = DisplayWindow::keyValue;
    int &x = MyPlayer::plyX;
    int &y = MyPlayer::plyY;
    int &d = MyPlayer::plyD;
    int i = x/32, j = y/32;

    qDebug() << x << " " << y << " " << d;

    switch (d)
    {
        case 0:p.drawImage(x, y, imgTank1Up); break;
        case 1:p.drawImage(x, y, imgTank1Down); break;
        case 2:p.drawImage(x, y, imgTank1Left); break;
        case 3:p.drawImage(x, y, imgTank1Right); break;
        default:p.drawImage(x, y, imgTank1Up);
    }

    switch (keyValue)
    {
        case 87:
            if (d == 0 && y > 0 && MyGlobal::boolMap[i][j - 1])
            {
                char n = MyGlobal::logicMap[i][j];
                switch (n)
                {
                    case 'G':p.drawImage(x, y, imgGrass); break;
                    case 'T':p.drawImage(x, y, imgTree); break;
                    case 'S':p.drawImage(x, y, imgSnow); break;
                    case 'M':p.drawImage(x, y, imgMarsh); break;
                    case 'R':p.drawImage(x, y, imgRock); break;
                    case 'W':p.drawImage(x, y, imgWater); break;
                    default:p.drawImage(x, y, imgGrass);
                }

                y -= PICHEIGHT;
                p.drawImage(x, y, imgTank1Up);
            }
            else
            {
                d = 0;
                p.drawImage(x, y, imgTank1Up);
            }
            break;
        case 83:
            if (d == 1 && y < 992 && MyGlobal::boolMap[i][j + 1])
            {
                char n = MyGlobal::logicMap[i][j];
                switch (n)
                {
                    case 'G':p.drawImage(x, y, imgGrass); break;
                    case 'T':p.drawImage(x, y, imgTree); break;
                    case 'S':p.drawImage(x, y, imgSnow); break;
                    case 'M':p.drawImage(x, y, imgMarsh); break;
                    case 'R':p.drawImage(x, y, imgRock); break;
                    case 'W':p.drawImage(x, y, imgWater); break;
                    default:p.drawImage(x, y, imgGrass);
                }

                y += PICHEIGHT;
                p.drawImage(x, y, imgTank1Down);
            }
            else
            {
                d = 1;
                p.drawImage(x, y, imgTank1Down);
            }
            break;
        case 65:
            if (d == 2 && x > 0 && MyGlobal::boolMap[i - 1][j])
            {
                char n = MyGlobal::logicMap[i][j];
                switch (n)
                {
                    case 'G':p.drawImage(x, y, imgGrass); break;
                    case 'T':p.drawImage(x, y, imgTree); break;
                    case 'S':p.drawImage(x, y, imgSnow); break;
                    case 'M':p.drawImage(x, y, imgMarsh); break;
                    case 'R':p.drawImage(x, y, imgRock); break;
                    case 'W':p.drawImage(x, y, imgWater); break;
                    default:p.drawImage(x, y, imgGrass);
                }

                x -= PICWIDTH;
                p.drawImage(x, y, imgTank1Left);
            }
            else
            {
                d = 2;
                p.drawImage(x, y, imgTank1Left);
            }
            break;
        case 68:
            if (d == 3 && x < 992 && MyGlobal::boolMap[i + 1][j])
            {
                char n = MyGlobal::logicMap[i][j];
                switch (n)
                {
                    case 'G':p.drawImage(x, y, imgGrass); break;
                    case 'T':p.drawImage(x, y, imgTree); break;
                    case 'S':p.drawImage(x, y, imgSnow); break;
                    case 'M':p.drawImage(x, y, imgMarsh); break;
                    case 'R':p.drawImage(x, y, imgRock); break;
                    case 'W':p.drawImage(x, y, imgWater); break;
                    default:p.drawImage(x, y, imgGrass);
                }

                x += PICWIDTH;
                p.drawImage(x, y, imgTank1Right);
            }
            else
            {
                d = 3;
                p.drawImage(x, y, imgTank1Right);
            }
            break;
    }
}

void DisplayWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "==Press a key";
    DisplayWindow::keyValue = event->key();
    //qDebug() << keyValue;
    //W-87
    //S-83
    //A-65
    //D-68
    switch(DisplayWindow::keyValue)
    {
        case 87:qDebug() << "W"; break;
        case 83:qDebug() << "S"; break;
        case 65:qDebug() << "A"; break;
        case 68:qDebug() << "D"; break;
        default:qDebug() << DisplayWindow::keyValue;
    }
    this->update();

}
