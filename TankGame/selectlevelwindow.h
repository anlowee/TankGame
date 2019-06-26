#ifndef SELECTLEVELWINDOW_H
#define SELECTLEVELWINDOW_H

#include <QWidget>

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
    void on_SelectLevelWindow_customContextMenuRequested(const QPoint &pos);

private:
    Ui::SelectLevelWindow *ui;
};

#endif // SELECTLEVELWINDOW_H
