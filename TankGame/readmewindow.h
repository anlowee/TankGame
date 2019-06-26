#ifndef READMEWINDOW_H
#define READMEWINDOW_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class ReadmeWindow;
}

class ReadmeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReadmeWindow(QWidget *parent = nullptr);
    ~ReadmeWindow();

private slots:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ReadmeWindow *ui;
};

#endif // READMEWINDOW_H
