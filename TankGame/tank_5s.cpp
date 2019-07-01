#include "tank_5s.h"
#include "ui_tank_5s.h"

Tank_5s::Tank_5s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_5s)
{
    ui->setupUi(this);
}

Tank_5s::~Tank_5s()
{
    delete ui;
}
