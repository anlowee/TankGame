#include "number_5.h"
#include "ui_number_5.h"

number_5::number_5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_5)
{
    ui->setupUi(this);
}

number_5::~number_5()
{
    delete ui;
}
