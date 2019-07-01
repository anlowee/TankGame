#include "defence_1.h"
#include "ui_defence_1.h"

Defence_1::Defence_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Defence_1)
{
    ui->setupUi(this);
}

Defence_1::~Defence_1()
{
    delete ui;
}
