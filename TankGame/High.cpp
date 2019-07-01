#include "High.h"
#include "ui_High.h"
#include <QString>
#include <QPixmap>
#include<QPushButton>
#include"number_1.h"
#include"number_2.h"
#include"number_3.h"
#include"number_4.h"
#include"number_5.h"
#include"level_1.h"
#include"level_2.h"
#include"level_3.h"
#include"level_4.h"
#include"level_5.h"
#include "myplayer.h"
#include <QPainter>
#include <QStyleOption>
#include <QPalette>
#include <QFont>

High::High(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::High)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("TankGame HIGH"));
            ui->beatnumbers->setText(QString::fromLocal8Bit("beatnumbers"));
            ui->beatlevels->setText(QString::fromLocal8Bit("beatlevels"));
            ui->beatnumbers->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
             ui->beatlevels->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
          QPalette a;
          a.setColor(QPalette::WindowText,Qt::white);
          ui->beatlevels->setPalette(a);
          ui->beatnumbers->setPalette(a);
         QFont font("黑体",10,75);
         ui->beatlevels->setFont(font);
         ui->beatnumbers->setFont(font);
             a1 = new level_1(this);
             a2 = new level_2(this);
             a3 = new level_3(this);
             a4 = new level_4(this);
             a5 = new level_5(this);
             b1 = new number_1(this);
             b2 = new number_2(this);
             b3 = new number_3(this);
             b4 = new number_4(this);
             b5 = new number_5(this);
             ui->stackedWidget->addWidget(a1);
             ui->stackedWidget->addWidget(a2);
             ui->stackedWidget->addWidget(a3);
             ui->stackedWidget->addWidget(a4);
             ui->stackedWidget->addWidget(a5);
             ui->stackedWidget->addWidget(b1);
             ui->stackedWidget->addWidget(b2);
             ui->stackedWidget->addWidget(b3);
             ui->stackedWidget->addWidget(b4);
             ui->stackedWidget->addWidget(b5);

       //kill achievement
       ui->lbl_6->setVisible(false);
       ui->lbl_7->setVisible(false);
       ui->lbl_8->setVisible(false);
       ui->lbl_9->setVisible(false);
       ui->lbl_10->setVisible(false);
       int kill = MyPlayer::plyKill;
       if (kill > 0)
           ui->lbl_6->setVisible(true);
       if (kill > 100)
           ui->lbl_7->setVisible(true);
       if (kill > 200)
           ui->lbl_8->setVisible(true);
       if (kill > 500)
           ui->lbl_9->setVisible(true);
       if (kill > 1000)
           ui->lbl_10->setVisible(true);

       //money achievement
       ui->lbl_1->setVisible(false);
       ui->lbl_2->setVisible(false);
       ui->lbl_3->setVisible(false);
       ui->lbl_4->setVisible(false);
       ui->lbl_5->setVisible(false);
       int mony = MyPlayer::plyMoney;
       if (mony > 0)
           ui->lbl_1->setVisible(true);
       if (mony > 50)
           ui->lbl_2->setVisible(true);
       if (mony > 100)
           ui->lbl_3->setVisible(true);
       if (mony > 150)
           ui->lbl_4->setVisible(true);
       if (mony > 200)
           ui->lbl_5->setVisible(true);

}
High::~High()
{
    delete ui;
}






void High::on_pushButton_1_clicked()
{
    ui->stackedWidget->setCurrentWidget(a1);
}

void High::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(a2);
}

void High::on_pushButton_3_clicked()
{
     ui->stackedWidget->setCurrentWidget(a3);
}

void High::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentWidget(a4);
}

void High::on_pushButton_5_clicked()
{
     ui->stackedWidget->setCurrentWidget(a5);
}

void High::on_pushButton_6_clicked()
{
     ui->stackedWidget->setCurrentWidget(b1);
}

void High::on_pushButton_7_clicked()
{
     ui->stackedWidget->setCurrentWidget(b2);
}

void High::on_pushButton_8_clicked()
{
     ui->stackedWidget->setCurrentWidget(b3);
}

void High::on_pushButton_9_clicked()
{
     ui->stackedWidget->setCurrentWidget(b4);
}

void High::on_pushButton_10_clicked()
{
     ui->stackedWidget->setCurrentWidget(b5);
}

void High::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

