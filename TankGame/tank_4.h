#ifndef TANK_4_H
#define TANK_4_H

#include <QWidget>

namespace Ui {
class Tank_4;
}

class Tank_4 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_4(QWidget *parent = nullptr);
    ~Tank_4();

private:
    Ui::Tank_4 *ui;
};

#endif // TANK_4_H
