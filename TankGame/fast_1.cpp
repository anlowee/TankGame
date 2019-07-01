#include "fast_1.h"
#include "ui_fast_1.h"

Fast_1::Fast_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fast_1)
{
    ui->setupUi(this);
}

Fast_1::~Fast_1()
{
    delete ui;
}
