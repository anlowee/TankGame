#ifndef TANK_10_H
#define TANK_10_H

#include <QWidget>

namespace Ui {
class Tank_10;
}

class Tank_10 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_10(QWidget *parent = nullptr);
    ~Tank_10();

private:
    Ui::Tank_10 *ui;
};

#endif // TANK_10_H
