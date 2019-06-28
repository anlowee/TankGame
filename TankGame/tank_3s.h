#ifndef TANK_3S_H
#define TANK_3S_H

#include <QWidget>

namespace Ui {
class Tank_3s;
}

class Tank_3s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_3s(QWidget *parent = nullptr);
    ~Tank_3s();

private:
    Ui::Tank_3s *ui;
};

#endif // TANK_3S_H
