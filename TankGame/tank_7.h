#ifndef TANK_7_H
#define TANK_7_H

#include <QWidget>

namespace Ui {
class Tank_7;
}

class Tank_7 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_7(QWidget *parent = nullptr);
    ~Tank_7();

private:
    Ui::Tank_7 *ui;
};

#endif // TANK_7_H
