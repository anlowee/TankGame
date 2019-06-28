#include "tank_reinforce.h"
#include "ui_tank_reinforce.h"
#include "shop.h"
Tank_reinforce::Tank_reinforce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tank_reinforce)
{
    ui->setupUi(this);
}

Tank_reinforce::~Tank_reinforce()
{
    delete ui;
}

void Tank_reinforce::on_backButton_clicked()
{
    Shop *b = new Shop(this);
    b->show();
}
