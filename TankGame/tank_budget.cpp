#include "tank_budget.h"
#include "ui_tank_budget.h"

Tank_budget::Tank_budget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_budget)
{
    ui->setupUi(this);
}

Tank_budget::~Tank_budget()
{
    delete ui;
}
