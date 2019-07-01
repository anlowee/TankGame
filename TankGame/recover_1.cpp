#include "recover_1.h"
#include "ui_recover_1.h"

Recover_1::Recover_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recover_1)
{
    ui->setupUi(this);
}

Recover_1::~Recover_1()
{
    delete ui;
}
