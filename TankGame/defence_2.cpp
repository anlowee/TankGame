#include "defence_2.h"
#include "ui_defence_2.h"

Defence_2::Defence_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Defence_2)
{
    ui->setupUi(this);
}

Defence_2::~Defence_2()
{
    delete ui;
}
