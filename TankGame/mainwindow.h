#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include"High.h"
#include "readmewindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void switchPage();

private slots:
    void on_btn_readme_clicked();

    void on_btn_high_clicked();

private:
    Ui::MainWindow *ui;
    High *a;
    ReadmeWindow *b;
};

#endif // MAINWINDOW_H
