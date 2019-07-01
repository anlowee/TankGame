#ifndef TANK_4S_H
#define TANK_4S_H

#include <QWidget>

namespace Ui {
class Tank_4s;
}

class Tank_4s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_4s(QWidget *parent = nullptr);
    ~Tank_4s();

private:
    Ui::Tank_4s *ui;
};

#endif // TANK_4S_H
