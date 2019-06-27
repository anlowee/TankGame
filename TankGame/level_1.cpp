#include "level_1.h"
#include "ui_level_1.h"

level_1::level_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::level_1)
{
    ui->setupUi(this);
}

level_1::~level_1()
{
    delete ui;
}
