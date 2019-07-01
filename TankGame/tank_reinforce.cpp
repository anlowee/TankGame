#include <QStackedWidget>
#include "tank_reinforce.h"
#include "ui_tank_reinforce.h"
#include "shop.h"
#include "attack_1.h"
#include "attack_2.h"
#include "defence_1.h"
#include "defence_2.h"
#include "fast_1.h"
#include "fast_2.h"
#include <QLabel>
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
   ++i;
   if(i==2){
   ui->attackButton->setEnabled(true);
   ui->stackedWidget->setCurrentWidget(a2);
   }
   else{
   ui->attackLabel->setVisible(true);
   ui->attackButton->setEnabled(false);
   ui->stackedWidget->setCurrentWidget(a2);
   }
}



void Tank_reinforce::on_defenceButton_clicked()
{
    ++j;
    if(j==2){
        ui->defenceButton->setEnabled(true);
        ui->stackedWidget_2->setCurrentWidget(b2);
    }
    else{
        ui->defenceLabel->setVisible(true);
        ui->defenceButton->setEnabled(false);
        ui->stackedWidget_2->setCurrentWidget(b2);
    }
}

void Tank_reinforce::on_fastButton_clicked()
{
    ++k;
    if(k==2){
        ui->fastButton->setEnabled(true);
        ui->stackedWidget_3->setCurrentWidget(c2);
    }
    else{
        ui->fastLabel->setVisible(true);
        ui->fastButton->setEnabled(false);
        ui->stackedWidget_3->setCurrentWidget(c2);
    }
}
