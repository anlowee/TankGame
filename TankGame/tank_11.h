#ifndef TANK_11_H
#define TANK_11_H

#include <QWidget>

namespace Ui {
class Tank_11;
}

class Tank_11 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_11(QWidget *parent = nullptr);
    ~Tank_11();

private:
    Ui::Tank_11 *ui;
};

#endif // TANK_11_H
