#ifndef TANK_1_H
#define TANK_1_H

#include <QWidget>

namespace Ui {
class Tank_1;
}

class Tank_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_1(QWidget *parent = nullptr);
    ~Tank_1();

private:
    Ui::Tank_1 *ui;
};

#endif // TANK_1_H
