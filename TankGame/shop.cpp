#include "shop.h"
#include "ui_shop.h"

Shop::Shop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    Tank_budget *a = new Tank_budget(this);
    Tank_reinforce *b = new Tank_reinforce(this);
    ui->stackedWidget->addWidget(a);
    ui->stackedWidget->addWidget(b);
}

Shop::~Shop()
{
    delete ui;
}


void Shop::on_reinforceButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(b);
}

void Shop::on_budgetButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(a);
}
