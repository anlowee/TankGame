#include "number_1.h"
#include "ui_number_1.h"
#include <QPalette>
#include <QFont>
number_1::number_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_1)
{
    ui->setupUi(this);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pa);
    QFont font("Microsoft YaHei",10,75);
    ui->label->setFont(font);
}

number_1::~number_1()
{
    delete ui;
}
