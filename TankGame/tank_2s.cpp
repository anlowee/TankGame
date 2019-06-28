#include "tank_2s.h"
#include "ui_tank_2s.h"

Tank_2s::Tank_2s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_2s)
{
    ui->setupUi(this);
}

Tank_2s::~Tank_2s()
{
    delete ui;
}
