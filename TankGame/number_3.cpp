#include "number_3.h"
#include "ui_number_3.h"
#include <QPalette>
#include <QFont>
number_3::number_3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_3)
{
    ui->setupUi(this);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pa);
    QFont font("Microsoft YaHei",10,75);
    ui->label->setFont(font);
}

number_3::~number_3()
{
    delete ui;
}
