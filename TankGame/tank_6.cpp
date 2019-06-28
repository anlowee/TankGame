#include "tank_6.h"
#include "ui_tank_6.h"

Tank_6::Tank_6(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_6)
{
    ui->setupUi(this);
}

Tank_6::~Tank_6()
{
    delete ui;
}
