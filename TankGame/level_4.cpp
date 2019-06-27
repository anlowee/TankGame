#include "level_4.h"
#include "ui_level_4.h"

level_4::level_4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::level_4)
{
    ui->setupUi(this);
}

level_4::~level_4()
{
    delete ui;
}
