#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readmewindow.h"
#include  "selectlevelwindow.h"
#include <QtGui>
#include <QFrame>
#include <QSoundEffect>
#include <QPixmap>
#include "High.h"
#include "myplayer.h"
#include "myglobal.h"
#include "mytank.h"
#include "shop.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //display bgm
    QSoundEffect *new_bgm = new QSoundEffect;
    QString dir = QCoreApplication::applicationDirPath();
    QString filename(dir + "/bgm.wav");
    new_bgm->setLoopCount(QSoundEffect::Infinite);
    new_bgm->setSource(QUrl::fromLocalFile(filename));
    new_bgm->setVolume(1.0);
    new_bgm->play();

    //load save data
    MyPlayer::plyMoney= MyGlobal::configIni->value("Player/Money", 0).toInt();
    MyPlayer::plyKill= MyGlobal::configIni->value("Player/Kills", 0).toInt();
    MyPlayer::plyAtk = MyGlobal::configIni->value("Player/PlayerATK", PLAYERATK).toDouble();
    MyPlayer::plyDef = MyGlobal::configIni->value("Player/PlayerDEF", PLAYERDEF).toDouble();
    MyPlayer::plySpeed = MyGlobal::configIni->value("Player/Speed", NORMALSPEED).toInt();
    MyPlayer::plyAtkSpeed = MyGlobal::configIni->value("Player/PlayerATKSpeed", 500).toInt();
    MyPlayer::plyMaxHlt = MyGlobal::configIni->value("Player/PlayerMaxHealth", PLAYERLIFE).toDouble();
    //0~11
    MyPlayer::tankForm = MyGlobal::configIni->value("Player/TankForm", 1).toInt();

    //load map img
    MyGlobal::LoadMapImg();
    //qDebug() << MyPlayer::plyMoney << MyPlayer::plyKill << MyPlayer::plyAtk << MyPlayer::plyDef << MyPlayer::plySpeed << MyPlayer::plyMaxHlt;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_readme_clicked()
{
    ReadmeWindow *new_w = new ReadmeWindow;
    new_w->show();
}

void MainWindow::on_btn_start_clicked()
{
    SelectLevelWindow *new_w = new SelectLevelWindow;
     new_w->show();
}

void MainWindow::on_btn_high_clicked()
{
    High *new_w= new High;
    new_w->show();
}

void MainWindow::on_pushButton_clicked()
{
    Shop *a = new Shop;
    a->show();
}
