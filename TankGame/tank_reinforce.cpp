#include <QStackedWidget>
#include "tank_reinforce.h"
#include "ui_tank_reinforce.h"
#include "shop.h"
#include "attack_1.h"
#include "attack_2.h"
#include "myplayer.h"
#include "myglobal.h"
#include "defence_1.h"
#include "nomoney.h"
#include "defence_2.h"
#include "fast_1.h"
#include "fast_2.h"
#include <QLabel>
#include <QFont>
#include <QPalette>
Tank_reinforce::Tank_reinforce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_reinforce)
{
    ui->setupUi(this);
    a1 = new Attack_1(this);
    a2 = new Attack_2(this);
    b1 = new Defence_1(this);
    b2 = new Defence_2(this);
    c1 = new Fast_1(this);
    c2 = new Fast_2(this);
    ui->stackedWidget->addWidget(a1);
    ui->stackedWidget->addWidget(a2);
    ui->stackedWidget_2->addWidget(b1);
    ui->stackedWidget_2->addWidget(b2);
    ui->stackedWidget_3->addWidget(c1);
    ui->stackedWidget_3->addWidget(c2);
    ui->stackedWidget->setCurrentWidget(a1);
    ui->stackedWidget_2->setCurrentWidget(b1);
    ui->stackedWidget_3->setCurrentWidget(c1);
    ui->attackLabel->setVisible(false);
    ui->defenceLabel->setVisible(false);
    ui->fastLabel->setVisible(false);
    QFont ft("Microsoft YaHei",10,75);
    ui->attackLabel->setFont(ft);
    ui->defenceLabel->setFont(ft);
    ui->fastLabel->setFont(ft);
    ui->backButton->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->attackLabel->setPalette(pa);
    ui->defenceLabel->setPalette(pa);
    ui->fastLabel->setPalette(pa);

    if (i >= 2 || MyPlayer::plyAtk >= 45.0)
    {
        ui->attackLabel->setVisible(true);
        ui->attackButton->setEnabled(false);
        ui->stackedWidget->setCurrentWidget(a2);
    }

    if (j >= 2 || MyPlayer::plyDef >= 10.0)
    {
        ui->defenceLabel->setVisible(true);
        ui->defenceButton->setEnabled(false);
        ui->stackedWidget_2->setCurrentWidget(b2);
    }

    if (k >= 2 || MyPlayer::plyAtkSpeed <= 300)
    {
        ui->fastLabel->setVisible(true);
        ui->fastButton->setEnabled(false);
        ui->stackedWidget_3->setCurrentWidget(c2);
    }
}

Tank_reinforce::~Tank_reinforce()
{
    delete ui;
}

void Tank_reinforce::on_backButton_clicked()
{
    Shop *b = new Shop(this);
    b->show();
}


void Tank_reinforce::on_attackButton_clicked()
{
    //is exceed max reinfore times(1)
    if (i >= 2 || MyPlayer::plyAtk >= 45.0)
    {
        ui->attackLabel->setVisible(true);
        ui->attackButton->setEnabled(false);
        ui->stackedWidget->setCurrentWidget(a2);
        return ;
    }

    //is have enough money
    if (MyPlayer::plyMoney < 30)
    {
        NoMoney *new_nm = new NoMoney;
        new_nm->show();
        return ;
    }

    //update
    ++i;
    MyPlayer::plyMoney -= 30;
    ui->attackButton->setEnabled(true);
    ui->stackedWidget->setCurrentWidget(a2);
    MyPlayer::plyAtk += 15;

    MyGlobal::SaveData();
}



void Tank_reinforce::on_defenceButton_clicked()
{
    //is exceed max reinfore times(1)
    if (j >= 2 || MyPlayer::plyDef >= 10.0)
    {
        ui->defenceLabel->setVisible(true);
        ui->defenceButton->setEnabled(false);
        ui->stackedWidget_2->setCurrentWidget(b2);
        return ;
    }

    //is have enough money
    if (MyPlayer::plyMoney < 30)
    {
        NoMoney *new_nm = new NoMoney;
        new_nm->show();
        return ;
    }

    //update
    ++j;
    MyPlayer::plyMoney -= 30;
    ui->defenceButton->setEnabled(true);
    ui->stackedWidget_2->setCurrentWidget(b2);
    MyPlayer::plyDef += 5;

    MyGlobal::SaveData();
}

void Tank_reinforce::on_fastButton_clicked()
{
    //is exceed max reinfore times(1)
    if (k >= 2 || MyPlayer::plyAtkSpeed <= 300)
    {
        ui->fastLabel->setVisible(true);
        ui->fastButton->setEnabled(false);
        ui->stackedWidget_3->setCurrentWidget(c2);
        return ;
    }

    //is have enough money
    if (MyPlayer::plyMoney < 30)
    {
        NoMoney *new_nm = new NoMoney;
        new_nm->show();
        return ;
    }

    ++k;
    MyPlayer::plyMoney -= 30;
    ui->fastButton->setEnabled(true);
    ui->stackedWidget_3->setCurrentWidget(c2);
    MyPlayer::plyAtkSpeed -= 200;

    MyGlobal::SaveData();
}
