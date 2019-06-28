#include "tank_2.h"
#include "ui_tank_2.h"

Tank_2::Tank_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_2)
{
    ui->setupUi(this);
}

Tank_2::~Tank_2()
{
    delete ui;
}
