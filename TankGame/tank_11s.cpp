#include "tank_11s.h"
#include "ui_tank_11s.h"

Tank_11s::Tank_11s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_11s)
{
    ui->setupUi(this);
}

Tank_11s::~Tank_11s()
{
    delete ui;
}
