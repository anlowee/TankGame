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
int MyPlayer::plyMoney;
int MyPlayer::plyKill;
int MyPlayer::ply2X;
int MyPlayer::ply2Y;
int MyPlayer::ply2D;
int MyPlayer::ply2Money;
int MyPlayer::ply2Kill;
double MyPlayer::plyAtk;
double MyPlayer::plyDef;
double MyPlayer::plyHlt;
double MyPlayer::ply2Atk;
double MyPlayer::ply2Def;
double MyPlayer::ply2Hlt;

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

void CreatPos2P(int mark)
{
    qsrand(time(NULL));
    for (int i = 0; i <= ENEMYNUMBER + 1; i++)
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
    //load
    freopen("save.sav", "r", stdin);
    int mny, kil;
    std::cin >> mny >> kil;
    MyPlayer::plyMoney = mny;
    MyPlayer::plyKill = kil;
    fclose(stdin);

    //pre
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

    //player's pos
    MyPlayer::plyX = (a_PutPos[ENEMYNUMBER].y)*PICWIDTH;
    MyPlayer::plyY = (a_PutPos[ENEMYNUMBER].x)*PICHEIGHT;
    MyPlayer::plyD = rand()%4;
    MyPlayer::plyAtk = PLAYERATK;
    MyPlayer::plyDef = PLAYERDEF;
    MyPlayer::plyHlt = PLAYERLIFE;

    //enemy's pos
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
    DisplayWindow::b_isTPM = false;
    new_w->show();
}

void SelectLevelWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SelectLevelWindow::on_pushButton_2_clicked()
{
    //pre
    MyMap *new_m =  new MyMap;
    new_m->CreateMap();
    DisplayWindow *new_w = new DisplayWindow;
    qsrand(time(NULL));

    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            b_PutMap[i][j] = true;
    int isPut = MyGlobal::m_TrueBlockMark;
    CreatPos2P(isPut);

    DisplayWindow::keyValue = NULL;
    qsrand(time(NULL));

    //1P's pos
    MyPlayer::plyX = (a_PutPos[ENEMYNUMBER].y)*PICWIDTH;
    MyPlayer::plyY = (a_PutPos[ENEMYNUMBER].x)*PICHEIGHT;
    MyPlayer::plyD = rand()%4;
    MyPlayer::plyAtk = PLAYERATK;
    MyPlayer::plyDef = PLAYERDEF;
    MyPlayer::plyHlt = PLAYERLIFE;

    //2P's pos
    MyPlayer::ply2X = (a_PutPos[ENEMYNUMBER + 1].y)*PICWIDTH;
    MyPlayer::ply2Y = (a_PutPos[ENEMYNUMBER + 1].x)*PICHEIGHT;
    MyPlayer::ply2D = rand()%4;
    MyPlayer::ply2Atk = PLAYERATK;
    MyPlayer::ply2Def = PLAYERDEF;
    MyPlayer::ply2Hlt = PLAYERLIFE;

    //enemy's pos
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
    new_w->b_isPlayer2Start = false;
    DisplayWindow::b_isTPM = true;
    new_w->show();
}
