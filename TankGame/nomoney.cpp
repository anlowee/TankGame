#include "nomoney.h"
#include "ui_nomoney.h"

NoMoney::NoMoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoMoney)
{
    ui->setupUi(this);
}

NoMoney::~NoMoney()
{
    delete ui;
}
