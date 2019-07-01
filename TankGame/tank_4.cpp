#include "tank_4.h"
#include "ui_tank_4.h"

Tank_4::Tank_4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_4)
{
    ui->setupUi(this);
}

Tank_4::~Tank_4()
{
    delete ui;
}
