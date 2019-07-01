#ifndef TANK_7S_H
#define TANK_7S_H

#include <QWidget>

namespace Ui {
class Tank_7s;
}

class Tank_7s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_7s(QWidget *parent = nullptr);
    ~Tank_7s();

private:
    Ui::Tank_7s *ui;
};

#endif // TANK_7S_H
