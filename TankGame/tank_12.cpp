#include "tank_12.h"
#include "ui_tank_12.h"

Tank_12::Tank_12(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_12)
{
    ui->setupUi(this);
}

Tank_12::~Tank_12()
{
    delete ui;
}
