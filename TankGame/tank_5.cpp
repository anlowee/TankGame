#include "tank_5.h"
#include "ui_tank_5.h"

Tank_5::Tank_5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_5)
{
    ui->setupUi(this);
}

Tank_5::~Tank_5()
{
    delete ui;
}
