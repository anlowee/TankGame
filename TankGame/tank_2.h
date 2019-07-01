#ifndef TANK_2_H
#define TANK_2_H

#include <QWidget>

namespace Ui {
class Tank_2;
}

class Tank_2 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_2(QWidget *parent = nullptr);
    ~Tank_2();

private:
    Ui::Tank_2 *ui;
};

#endif // TANK_2_H
