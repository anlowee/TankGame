#include "displaywindow.h"
#include "ui_displaywindow.h"
#include <QPainter>
#include <QStyleOption>
#include <QImage>

DisplayWindow::DisplayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);

    /*
    QImage imgGrass("grass.png");
    QImage imgFactory("factory.png");
    QImage imgRock("rock.png");
    QImage imgMarsh("marsh.png");
    QImage imgSnow("snow.png");
    QImage imgTree("tree.png");
    QImage imgWater("water.png");
    */

}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

