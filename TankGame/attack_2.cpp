#include "attack_2.h"
#include "ui_attack_2.h"

Attack_2::Attack_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Attack_2)
{
    ui->setupUi(this);
}

Attack_2::~Attack_2()
{
    delete ui;
}
