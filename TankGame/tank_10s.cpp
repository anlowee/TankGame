#include "tank_10s.h"
#include "ui_tank_10s.h"

Tank_10s::Tank_10s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_10s)
{
    ui->setupUi(this);
}

Tank_10s::~Tank_10s()
{
    delete ui;
}
