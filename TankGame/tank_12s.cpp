#include "tank_12s.h"
#include "ui_tank_12s.h"

Tank_12s::Tank_12s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_12s)
{
    ui->setupUi(this);
}

Tank_12s::~Tank_12s()
{
    delete ui;
}
