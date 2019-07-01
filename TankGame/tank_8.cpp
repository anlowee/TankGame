#include "tank_8.h"
#include "ui_tank_8.h"

Tank_8::Tank_8(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_8)
{
    ui->setupUi(this);
}

Tank_8::~Tank_8()
{
    delete ui;
}
