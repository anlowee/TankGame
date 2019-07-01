#include "tank_6s.h"
#include "ui_tank_6s.h"

Tank_6s::Tank_6s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_6s)
{
    ui->setupUi(this);
}

Tank_6s::~Tank_6s()
{
    delete ui;
}
