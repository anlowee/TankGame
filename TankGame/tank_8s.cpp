#include "tank_8s.h"
#include "ui_tank_8s.h"

Tank_8s::Tank_8s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_8s)
{
    ui->setupUi(this);
}

Tank_8s::~Tank_8s()
{
    delete ui;
}
