#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include "tank_budget.h"
#include "tank_reinforce.h"
#include <QStackedWidget>
namespace Ui {
class Shop;
}

class Shop : public QWidget
{
    Q_OBJECT

public:
    explicit Shop(QWidget *parent = nullptr);
    ~Shop();

private slots:

    void on_reinforceButton_clicked();

    void on_budgetButton_clicked();

private:
    Ui::Shop *ui;
    Tank_budget *a;
    Tank_reinforce *b;

};

#endif // SHOP_H
