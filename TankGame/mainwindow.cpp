#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readmewindow.h"
#include <QtGui>
#include <QFrame>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    a=new High(this);
    b=new ReadmeWindow(this);
    ui->stackedWidget->addWidget(a);
    ui->stackedWidget->addWidget(b);
    ui->stackedWidget->setCurrentWidget(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_readme_clicked()
{
    ui->stackedWidget->setCurrentWidget(b);

}

void MainWindow::on_btn_high_clicked()
{
    ui->stackedWidget->setCurrentWidget(a);
}

