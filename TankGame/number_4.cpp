#include "number_4.h"
#include "ui_number_4.h"

number_4::number_4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_4)
{
    ui->setupUi(this);
}

number_4::~number_4()
{
    delete ui;
}
