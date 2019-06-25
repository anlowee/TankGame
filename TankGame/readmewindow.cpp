#include "readmewindow.h"
#include "ui_readmewindow.h"

ReadmeWindow::ReadmeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadmeWindow)
{
    ui->setupUi(this);
}

ReadmeWindow::~ReadmeWindow()
{
    delete ui;
}
