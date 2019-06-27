#include "number_3.h"
#include "ui_number_3.h"

number_3::number_3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_3)
{
    ui->setupUi(this);
}

number_3::~number_3()
{
    delete ui;
}
