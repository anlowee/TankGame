#include "tank_7s.h"
#include "ui_tank_7s.h"

Tank_7s::Tank_7s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_7s)
{
    ui->setupUi(this);
}

Tank_7s::~Tank_7s()
{
    delete ui;
}
