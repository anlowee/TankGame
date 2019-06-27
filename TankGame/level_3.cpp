#include "level_3.h"
#include "ui_level_3.h"

level_3::level_3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::level_3)
{
    ui->setupUi(this);
}

level_3::~level_3()
{
    delete ui;
}
