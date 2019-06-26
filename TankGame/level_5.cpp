#include "level_5.h"
#include "ui_level_5.h"

level_5::level_5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::level_5)
{
    ui->setupUi(this);
}

level_5::~level_5()
{
    delete ui;
}
