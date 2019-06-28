#ifndef TANK_5S_H
#define TANK_5S_H

#include <QWidget>

namespace Ui {
class Tank_5s;
}

class Tank_5s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_5s(QWidget *parent = nullptr);
    ~Tank_5s();

private:
    Ui::Tank_5s *ui;
};

#endif // TANK_5S_H
