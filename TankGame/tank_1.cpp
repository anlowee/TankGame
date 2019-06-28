#include "tank_1.h"
#include "ui_tank_1.h"

Tank_1::Tank_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_1)
{
    ui->setupUi(this);
}

Tank_1::~Tank_1()
{
    delete ui;
}
