#include "tank_budget.h"
#include "ui_tank_budget.h"
#include "shop.h"
#include "nomoney.h"
#include "myglobal.h"
#include <QStackedWidget>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include "recover_1.h"
#include "recover_2.h"
#include "tank_1.h"
#include "tank_10.h"
#include "tank_11.h"
#include "tank_12.h"
#include "tank_2.h"
#include "tank_3.h"
#include "tank_4.h"
#include "tank_5.h"
#include "tank_6.h"
#include "tank_7.h"
#include "tank_8.h"
#include "tank_9.h"
#include "tank_1s.h"
#include "tank_10s.h"
#include "tank_11s.h"
#include "tank_12s.h"
#include "tank_2s.h"
#include "tank_3s.h"
#include "tank_4s.h"
#include "tank_5s.h"
#include "tank_6s.h"
#include "tank_7s.h"
#include "tank_8s.h"
#include "tank_9s.h"
#include "myplayer.h"
#include <QFont>
#include <QPalette>

Tank_budget::Tank_budget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_budget)
{
    ui->setupUi(this);
    a = new Recover_1(this);
    b = new Recover_2(this);
    c1 = new Tank_1(this);
    c2 = new Tank_2(this);
    c3 = new Tank_3(this);
    c4 = new Tank_4(this);
    c5 = new Tank_5(this);
    c6 = new Tank_6(this);
    c7 = new Tank_7(this);
    c8 = new Tank_8(this);
    c9 = new Tank_9(this);
    c10 = new Tank_10(this);
    c11 = new Tank_11(this);
    c12 = new Tank_12(this);
    d1 = new Tank_1s(this);
    d2 = new Tank_2s(this);
    d3 = new Tank_3s(this);
    d4 = new Tank_4s(this);
    d5 = new Tank_5s(this);
    d6 = new Tank_6s(this);
    d7 = new Tank_7s(this);
    d8 = new Tank_8s(this);
    d9 = new Tank_9s(this);
    d10 = new Tank_10s(this);
    d11 = new Tank_11s(this);
    d12 = new Tank_12s(this);
    ui->stackedWidget->addWidget(a);
    ui->stackedWidget->addWidget(b);
    ui->stackedWidget->setCurrentWidget(a);
    ui->recoverLabel->setVisible(false);
    ui->stackedWidget_2->addWidget(c1);
    ui->stackedWidget_2->addWidget(c2);
    ui->stackedWidget_2->addWidget(c3);
    ui->stackedWidget_2->addWidget(c4);
    ui->stackedWidget_2->addWidget(c5);
    ui->stackedWidget_2->addWidget(c6);
    ui->stackedWidget_2->addWidget(c7);
    ui->stackedWidget_2->addWidget(c8);
    ui->stackedWidget_2->addWidget(c9);
    ui->stackedWidget_2->addWidget(c10);
    ui->stackedWidget_2->addWidget(c11);
    ui->stackedWidget_2->addWidget(c12);
    ui->stackedWidget_2->setCurrentWidget(c1);
    ui->tankLable->setVisible(false);
    ui->stackedWidget_3->addWidget(d1);
    ui->stackedWidget_3->addWidget(d2);
    ui->stackedWidget_3->addWidget(d3);
    ui->stackedWidget_3->addWidget(d4);
    ui->stackedWidget_3->addWidget(d5);
    ui->stackedWidget_3->addWidget(d6);
    ui->stackedWidget_3->addWidget(d7);
    ui->stackedWidget_3->addWidget(d8);
    ui->stackedWidget_3->addWidget(d9);
    ui->stackedWidget_3->addWidget(d10);
    ui->stackedWidget_3->addWidget(d11);
    ui->stackedWidget_3->addWidget(d12);
    ui->stackedWidget_3->setCurrentWidget(d1);
    QFont ft("Microsoft YaHei",10,75);
    ui->recoverLabel->setFont(ft);
    ui->tankLable->setFont(ft);
    ui->backButton->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->recoverLabel->setPalette(pa);
    ui->tankLable->setPalette(pa);
}

Tank_budget::~Tank_budget()
{
    delete ui;
}

void Tank_budget::on_backButton_clicked()
{
  Shop *a = new Shop(this);
  a->show();
}

void Tank_budget::on_recoverButton_clicked()
{
    //is exceed max reinfore times(1)
    if (i >= 2)
    {
        ui->recoverLabel->setVisible(true);
        ui->recoverButton->setEnabled(false);
        ui->stackedWidget->setCurrentWidget(b);
        return ;
    }

    //is have enough money
    if (MyPlayer::plyMoney < 10)
    {
        NoMoney *new_nm = new NoMoney;
        new_nm->show();
        return ;
    }

    //update
    ++i;
    MyPlayer::plyMoney -= 10;
    ui->recoverButton->setEnabled(true);
    ui->stackedWidget->setCurrentWidget(b);
    MyPlayer::plyMaxHlt += 100.0;

    MyGlobal::SaveData();
}
void Tank_budget::on_levelUpButton_clicked()
{
    //is have enough money
    if (MyPlayer::plyMoney < 20)
    {
        NoMoney *new_nm = new NoMoney;
        new_nm->show();
        return ;
    }

    //buy the new tank
    ++j;
    MyPlayer::plyMoney -= 20;
    switch(j){
         case 2:
        ui->stackedWidget_2->setCurrentWidget(c2);
        ui->stackedWidget_3->setCurrentWidget(d2);
        MyPlayer::tankForm = 1;
        MyGlobal::SaveData();
        break;
         case 3:
        ui->stackedWidget_2->setCurrentWidget(c3);
        ui->stackedWidget_3->setCurrentWidget(d3);
        MyPlayer::tankForm = 2;
        MyGlobal::SaveData();
        break;
         case 4:
        ui->stackedWidget_2->setCurrentWidget(c4);
        ui->stackedWidget_3->setCurrentWidget(d4);
        MyPlayer::tankForm = 3;
        MyGlobal::SaveData();
        break;
         case 5:
        ui->stackedWidget_2->setCurrentWidget(c5);
        ui->stackedWidget_3->setCurrentWidget(d5);
        MyPlayer::tankForm = 4;
        MyGlobal::SaveData();
        break;
         case 6:
        ui->stackedWidget_2->setCurrentWidget(c6);
        ui->stackedWidget_3->setCurrentWidget(d6);
        MyPlayer::tankForm = 5;
        MyGlobal::SaveData();
        break;
         case 7:
        ui->stackedWidget_2->setCurrentWidget(c7);
        ui->stackedWidget_3->setCurrentWidget(d7);
        MyPlayer::tankForm = 6;
        MyGlobal::SaveData();
        break;
         case 8:
        ui->stackedWidget_2->setCurrentWidget(c8);
        ui->stackedWidget_3->setCurrentWidget(d8);
        MyPlayer::tankForm = 7;
        MyGlobal::SaveData();
        break;
         case 9:
        ui->stackedWidget_2->setCurrentWidget(c9);
        ui->stackedWidget_3->setCurrentWidget(d9);
        MyPlayer::tankForm = 8;
        MyGlobal::SaveData();
        break;
         case 10:
        ui->stackedWidget_2->setCurrentWidget(c10);
        ui->stackedWidget_3->setCurrentWidget(d10);
        MyPlayer::tankForm = 9;
        MyGlobal::SaveData();
        break;
         case 11:
        ui->stackedWidget_2->setCurrentWidget(c11);
        ui->stackedWidget_3->setCurrentWidget(d11);
        MyPlayer::tankForm = 10;
        MyGlobal::SaveData();
        break;
         case 12:
        ui->stackedWidget_2->setCurrentWidget(c12);
        ui->stackedWidget_3->setCurrentWidget(d12);
        MyPlayer::tankForm = 11;
        MyGlobal::SaveData();
        break;
    default:
         ui->stackedWidget_2->setCurrentWidget(c12);
         ui->stackedWidget_3->setCurrentWidget(d12);
         ui->tankLable->setVisible(true);
    }
}
