#include "selectlevelwindow.h"
#include "ui_selectlevelwindow.h"
#include "displaywindow.h"
#include <QPainter>
#include <QStyleOption>
#include "mymap.h"

SelectLevelWindow::SelectLevelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectLevelWindow)
{
    ui->setupUi(this);
}

SelectLevelWindow::~SelectLevelWindow()
{
    delete ui;
}


void SelectLevelWindow::on_pushButton_clicked()
{
    DisplayWindow *new_w = new DisplayWindow;
    new_w->show();
    //for debug
    MyMap *new_m = new MyMap;
    new_m->CreateMap();
    new_m->DrawMap();
    //----------
}

void SelectLevelWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
