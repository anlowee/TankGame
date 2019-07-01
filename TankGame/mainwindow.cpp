#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readmewindow.h"
#include  "selectlevelwindow.h"
#include <QtGui>
#include <QFrame>
#include <QSoundEffect>
#include "myplayer.h"
#include <QPixmap>
#include "myglobal.h"
#include"High.h"

int MyPlayer::plyMoney;
int MyPlayer::plyKill;

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

    //load
    MyPlayer::plyMoney=MyGlobal::configIni->value("Player/Money").toInt();
    MyPlayer::plyKill=MyGlobal::configIni->value("Player/Kills").toInt();
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
