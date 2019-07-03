#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_readme_clicked();

    void on_btn_start_clicked();

    void on_btn_high_clicked();

    void on_pushButton_clicked();

    void reshow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
