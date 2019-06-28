#include "displaywindow.h"
#include "ui_displaywindow.h"
#include "mymap.h"
#include <QPainter>
#include <QStyleOption>
#include <QImage>
#include <iostream>
#include "myglobal.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
//    p.drawText(QPointF(100, 100), "A");
//    p.drawLine(10,10,400,400);
//    return;
    //p.drawText()
/*
    for (int i = 0; i < INUM; i++)
    {
        for (int j = 0; j < JNUM; j++)
            std::cout << MyGlobal::logicMap[i][j] << " ";
        std::cout << std::endl;
    }
*/

    QImage imgGrass("grass.png");
    QImage imgRock("rock.png");
    QImage imgSnow("snow.png");
    QImage imgMarsh("marsh.png");
    QImage imgTree("tree.png");
    QImage imgWater("water.png");

    //p.drawImage(10,10,imgGrass);

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
}

