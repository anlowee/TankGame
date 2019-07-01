#include "tank_3s.h"
#include "ui_tank_3s.h"

Tank_3s::Tank_3s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_3s)
{
    ui->setupUi(this);
}

Tank_3s::~Tank_3s()
{
    delete ui;
}
