#ifndef TANK_6S_H
#define TANK_6S_H

#include <QWidget>

namespace Ui {
class Tank_6s;
}

class Tank_6s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_6s(QWidget *parent = nullptr);
    ~Tank_6s();

private:
    Ui::Tank_6s *ui;
};

#endif // TANK_6S_H
