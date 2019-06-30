#include "selectlevelwindow.h"
#include "ui_selectlevelwindow.h"
#include "displaywindow.h"
#include <QPainter>
#include <iostream>
#include <QStyleOption>
#include <set>
#include "mymap.h"
#include "myplayer.h"
#include "myenemy.h"
#include "myglobal.h"

int MyPlayer::plyX;
int MyPlayer::plyY;
int MyPlayer::plyD;
int MyPlayer::plyMoney = 0;
double MyPlayer::plyAtk;
double MyPlayer::plyDef;
double MyPlayer::plyHlt;
MyEnemy a_EnemyTank[100];//fix
//int MyGlobal::dfsMap[1005][1005];

bool b_PutMap[1005][1005];
struct PutPos
{
    int x, y;
} a_PutPos[1000000];
std::set <PutPos> s_PutPos;

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

void CreatPos(int mark)
{
    qsrand(time(NULL));
    for (int i = 0; i <= ENEMYNUMBER; i++)
    {
        int x = rand()%32, y = rand()%32;
        while (MyGlobal::dfsMap[x][y] != mark || !b_PutMap[x][y])
        {
            x = rand()%32;
            y = rand()%32;
        }

        b_PutMap[x][y] = false;
        a_PutPos[i].x = x;
        a_PutPos[i].y = y;
    }
}

void SelectLevelWindow::on_pushButton_clicked()
{
    MyMap *new_m =  new MyMap;
    new_m->CreateMap();
    DisplayWindow *new_w = new DisplayWindow;
    qsrand(time(NULL));

    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            b_PutMap[i][j] = true;
    int isPut = MyGlobal::m_TrueBlockMark;
    CreatPos(isPut);

    DisplayWindow::keyValue = NULL;
    qsrand(time(NULL));
    MyPlayer::plyX = (a_PutPos[ENEMYNUMBER].y)*PICWIDTH;
    MyPlayer::plyY = (a_PutPos[ENEMYNUMBER].x)*PICHEIGHT;
    MyPlayer::plyD = rand()%4;
    MyPlayer::plyAtk = PLAYERATK;
    MyPlayer::plyDef = PLAYERDEF;
    MyPlayer::plyHlt = PLAYERLIFE;

    for (int i = 0; i < ENEMYNUMBER; i++)
    {
        a_EnemyTank[i].SetX((a_PutPos[i].y)*PICWIDTH);
        a_EnemyTank[i].SetY((a_PutPos[i].x)*PICHEIGHT);
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
