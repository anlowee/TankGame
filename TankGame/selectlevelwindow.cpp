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
int MyPlayer::plyMoney = 0;
double MyPlayer::plyAtk;
double MyPlayer::plyDef;
double MyPlayer::plyHlt;
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
    MyPlayer::plyAtk = PLAYERATK;
    MyPlayer::plyDef = PLAYERDEF;
    MyPlayer::plyHlt = PLAYERLIFE;

    for (int i = 0; i < ENEMYNUMBER; i++)
    {
        a_EnemyTank[i].SetX((rand()%32)*PICWIDTH);
        a_EnemyTank[i].SetY((rand()%32)*PICHEIGHT);
        a_EnemyTank[i].SetDir(rand()%4);
        a_EnemyTank[i].SetAtk(ENEMYATK);
        a_EnemyTank[i].SetDef(ENEMYDEF);
        a_EnemyTank[i].SetHlt(ENEMYLIFE);
        a_EnemyTank[i].SetDisappear(false);
    }

    new_w->cntBullets = 0;
    new_w->cntEnemy = ENEMYNUMBER;
    new_w->b_isPlayerStart = false;
    extern MyEnemy a_EnemyTank[100];
    new_w->show();
}

void SelectLevelWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
