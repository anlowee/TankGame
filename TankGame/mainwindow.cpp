#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readmewindow.h"
#include  "selectlevelwindow.h"
#include <QtGui>
#include <QFrame>
#include <QPixmap>
#include"High.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
