#include "tank_7.h"
#include "ui_tank_7.h"

Tank_7::Tank_7(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_7)
{
    ui->setupUi(this);
}

Tank_7::~Tank_7()
{
    delete ui;
}
