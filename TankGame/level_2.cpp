#include "level_2.h"
#include "ui_level_2.h"

level_2::level_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::level_2)
{
    ui->setupUi(this);
}

level_2::~level_2()
{
    delete ui;
}
