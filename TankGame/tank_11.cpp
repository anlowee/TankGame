#include "tank_11.h"
#include "ui_tank_11.h"

Tank_11::Tank_11(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_11)
{
    ui->setupUi(this);
}

Tank_11::~Tank_11()
{
    delete ui;
}
