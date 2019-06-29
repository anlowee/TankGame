#include "selectlevelwindow.h"
#include "ui_selectlevelwindow.h"
#include "displaywindow.h"
#include <QPainter>
#include <QStyleOption>
#include "mymap.h"
#include "myplayer.h"
#include "myenemy.h"

int MyPlayer::plyX;
int MyPlayer::plyY;
int MyPlayer::plyD;
MyEnemy a_EnemyTank[100];//fix

SelectLevelWindow::SelectLevelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectLevelWindow)
{
    ui->setupUi(this);
}

SelectLevelWindow::~SelectLevelWindow()
{
    delete ui;
}


void SelectLevelWindow::on_pushButton_clicked()
{
    MyMap *new_m =  new MyMap;
    new_m->CreateMap();
    DisplayWindow *new_w = new DisplayWindow;
    DisplayWindow::keyValue = NULL;
    qsrand(time(NULL));
    MyPlayer::plyX = (rand()%32)*PICWIDTH;
    MyPlayer::plyY = (rand()%32)*PICHEIGHT;
    MyPlayer::plyD = rand()%4;

    for (int i = 0; i < ENEMYNUMBER; i++)
    {
        a_EnemyTank[i].SetX((rand()%32)*PICWIDTH);
        a_EnemyTank[i].SetY((rand()%32)*PICHEIGHT);
        a_EnemyTank[i].SetDir(rand()%4);
    }

    new_w->show();
}

void SelectLevelWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
