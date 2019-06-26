#include "selectlevelwindow.h"
#include "ui_selectlevelwindow.h"

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

void SelectLevelWindow::on_SelectLevelWindow_customContextMenuRequested(const QPoint &pos)
{

}
