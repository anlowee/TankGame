#ifndef NOMONEY_H
#define NOMONEY_H

#include <QDialog>

namespace Ui {
class NoMoney;
}

class NoMoney : public QDialog
{
    Q_OBJECT

public:
    explicit NoMoney(QWidget *parent = nullptr);
    ~NoMoney();

private:
    Ui::NoMoney *ui;
};

#endif // NOMONEY_H
