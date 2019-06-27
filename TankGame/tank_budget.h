#ifndef TANK_BUDGET_H
#define TANK_BUDGET_H

#include <QWidget>

namespace Ui {
class Tank_budget;
}

class Tank_budget : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_budget(QWidget *parent = nullptr);
    ~Tank_budget();

private:
    Ui::Tank_budget *ui;
};

#endif // TANK_BUDGET_H
