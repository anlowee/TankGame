#include "shop.h"
#include "ui_shop.h"
#include <QFont>
Shop::Shop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    a = new Tank_budget(this);
    b = new Tank_reinforce(this);
    ui->stackedWidget->addWidget(a);
    ui->stackedWidget->addWidget(b);
    QFont font("Microsoft YaHei",10,75);
    ui->reinforceButton->setFont(font);
    ui->budgetButton->setFont(font);
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
void Shop::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
