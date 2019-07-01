#include "attack_1.h"
#include "ui_attack_1.h"

Attack_1::Attack_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Attack_1)
{
    ui->setupUi(this);
}

Attack_1::~Attack_1()
{
    delete ui;
}
