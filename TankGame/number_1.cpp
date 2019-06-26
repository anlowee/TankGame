#include "number_1.h"
#include "ui_number_1.h"

number_1::number_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_1)
{
    ui->setupUi(this);
}

number_1::~number_1()
{
    delete ui;
}
