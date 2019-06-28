#include "tank_1s.h"
#include "ui_tank_1s.h"

Tank_1s::Tank_1s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_1s)
{
    ui->setupUi(this);
}

Tank_1s::~Tank_1s()
{
    delete ui;
}
