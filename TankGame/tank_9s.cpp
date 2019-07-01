#include "tank_9s.h"
#include "ui_tank_9s.h"

Tank_9s::Tank_9s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_9s)
{
    ui->setupUi(this);
}

Tank_9s::~Tank_9s()
{
    delete ui;
}
