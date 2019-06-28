#ifndef TANK_8_H
#define TANK_8_H

#include <QWidget>

namespace Ui {
class Tank_8;
}

class Tank_8 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_8(QWidget *parent = nullptr);
    ~Tank_8();

private:
    Ui::Tank_8 *ui;
};

#endif // TANK_8_H
