#include "fast_2.h"
#include "ui_fast_2.h"

Fast_2::Fast_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fast_2)
{
    ui->setupUi(this);
}

Fast_2::~Fast_2()
{
    delete ui;
}
