#ifndef TANK_5_H
#define TANK_5_H

#include <QWidget>

namespace Ui {
class Tank_5;
}

class Tank_5 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_5(QWidget *parent = nullptr);
    ~Tank_5();

private:
    Ui::Tank_5 *ui;
};

#endif // TANK_5_H
