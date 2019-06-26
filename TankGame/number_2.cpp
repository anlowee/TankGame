#include "number_2.h"
#include "ui_number_2.h"

number_2::number_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_2)
{
    ui->setupUi(this);
}

number_2::~number_2()
{
    delete ui;
}
