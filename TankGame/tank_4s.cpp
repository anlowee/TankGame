#include "tank_4s.h"
#include "ui_tank_4s.h"

Tank_4s::Tank_4s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_4s)
{
    ui->setupUi(this);
}

Tank_4s::~Tank_4s()
{
    delete ui;
}
