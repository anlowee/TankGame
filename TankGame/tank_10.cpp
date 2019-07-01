#include "tank_10.h"
#include "ui_tank_10.h"

Tank_10::Tank_10(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_10)
{
    ui->setupUi(this);
}

Tank_10::~Tank_10()
{
    delete ui;
}
