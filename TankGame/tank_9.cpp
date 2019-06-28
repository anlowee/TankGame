#include "tank_9.h"
#include "ui_tank_9.h"

Tank_9::Tank_9(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_9)
{
    ui->setupUi(this);
}

Tank_9::~Tank_9()
{
    delete ui;
}
