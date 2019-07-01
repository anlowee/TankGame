#include "recover_2.h"
#include "ui_recover_2.h"

Recover_2::Recover_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recover_2)
{
    ui->setupUi(this);
}

Recover_2::~Recover_2()
{
    delete ui;
}
