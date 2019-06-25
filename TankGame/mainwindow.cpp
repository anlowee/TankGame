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

    connect(this->ui->btn_readme, SIGNAL(clicked()), SLOT(on_btn_readme_clicked()));
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
