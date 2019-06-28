#include "tank_3.h"
#include "ui_tank_3.h"

Tank_3::Tank_3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_3)
{
    ui->setupUi(this);
}

Tank_3::~Tank_3()
{
    delete ui;
}
