#ifndef SELECTLEVELWINDOW_H
#define SELECTLEVELWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include "mainwindow.h"

namespace Ui {
class SelectLevelWindow;
}

class SelectLevelWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SelectLevelWindow(QWidget *parent = nullptr);
    ~SelectLevelWindow();

private slots:

    void paintEvent(QPaintEvent *event);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SelectLevelWindow *ui;
    MainWindow *back;
    bool is_close;
};

#endif // SELECTLEVELWINDOW_H
