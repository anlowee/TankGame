#ifndef TANK_6_H
#define TANK_6_H

#include <QWidget>

namespace Ui {
class Tank_6;
}

class Tank_6 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_6(QWidget *parent = nullptr);
    ~Tank_6();

private:
    Ui::Tank_6 *ui;
};

#endif // TANK_6_H
