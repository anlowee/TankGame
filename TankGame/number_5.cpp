#include "number_5.h"
#include "ui_number_5.h"
#include <QPalette>
#include <QFont>
number_5::number_5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_5)
{
    ui->setupUi(this);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pa);
    QFont font("Microsoft YaHei",10,75);
    ui->label->setFont(font);
}

number_5::~number_5()
{
    delete ui;
}
