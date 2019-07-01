#include "number_2.h"
#include "ui_number_2.h"
#include <QPalette>
#include <QFont>
number_2::number_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_2)
{
    ui->setupUi(this);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pa);
    QFont font("Microsoft YaHei",10,75);
    ui->label->setFont(font);
}

number_2::~number_2()
{
    delete ui;
}
