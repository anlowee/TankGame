#include "number_4.h"
#include "ui_number_4.h"
#include <QPalette>
#include <QFont>
number_4::number_4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::number_4)
{
    ui->setupUi(this);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pa);
    QFont font("Microsoft YaHei",10,75);
    ui->label->setFont(font);
}

number_4::~number_4()
{
    delete ui;
}
