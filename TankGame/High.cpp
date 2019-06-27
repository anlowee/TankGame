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
     ui->stackedWidget->setCurrentWidget(b3);
}

void High::on_pushButton_10_clicked()
{
     ui->stackedWidget->setCurrentWidget(b4);
}


