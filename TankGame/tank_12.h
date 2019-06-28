#ifndef TANK_12_H
#define TANK_12_H

#include <QWidget>

namespace Ui {
class Tank_12;
}

class Tank_12 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_12(QWidget *parent = nullptr);
    ~Tank_12();

private:
    Ui::Tank_12 *ui;
};

#endif // TANK_12_H
