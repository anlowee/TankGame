#include "High.h"
#include "ui_High.h"
#include <QString>
#include <QPixmap>
#include<QPushButton>
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
             ui->pictureLable1->setScaledContents(true);
             ui->pictureLable2->setScaledContents(true);
             connect(ui->nextButton1,SIGNAL(clicked()),this,SLOT(on_nextButton1_clicked()));
             connect(ui->nextButton2,SIGNAL(clicked()),this,SLOT(on_nextButton2_clicked()));
}
High::~High()
{
    delete ui;
}
void High::initPictureList1(){
    for(int i=1;i<=5;i++){
        QString path = "D:/391/WHU/TankGame/sample/photo/High_pic/High_beatnumbers_"+QString::number(i)+".jpg";
        pictureList1.push_back(path);
    }
}
void High::initPictureList2(){
    for(int i=1;i<=5;i++){
        QString path ="D:/391/WHU/TankGame/sample/photo/High_pic/High_beatlevels_"+QString::number(i)+".jpg";
        pictureList2.push_back(path);
    }
}


void High::on_nextButton1_clicked()
{
    for (pictureNumber1=1;ui->pictureLable1->pixmap()!=0;++pictureNumber1){
    ui->pictureLable1->setPixmap(QPixmap(pictureList1[pictureNumber1]));
    if(pictureNumber1>=5){
        pictureNumber1=1;
    }
    if(pictureNumber1!=0){
    ui->nextButton1->setEnabled(true);
      }
   }
}

void High::on_nextButton2_clicked()
{
    for (pictureNumber2=1;ui->pictureLable2->pixmap()!=0;++pictureNumber2){
    ui->pictureLable2->setPixmap(QPixmap(pictureList2[pictureNumber2]));
    if(pictureNumber2>=5){
        pictureNumber2=1;
    }
    if(pictureNumber2!=0){
    ui->nextButton1->setEnabled(true);
      }
   }
}

