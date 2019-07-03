#include "readmewindow.h"
#include "ui_readmewindow.h"
#include <QStyleOption>
#include <QPainter>

ReadmeWindow::ReadmeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadmeWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

ReadmeWindow::~ReadmeWindow()
{
    delete ui;
}

void ReadmeWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
