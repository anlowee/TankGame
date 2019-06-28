#ifndef TANK_3_H
#define TANK_3_H

#include <QWidget>

namespace Ui {
class Tank_3;
}

class Tank_3 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_3(QWidget *parent = nullptr);
    ~Tank_3();

private:
    Ui::Tank_3 *ui;
};

#endif // TANK_3_H
