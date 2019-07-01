#ifndef TANK_10S_H
#define TANK_10S_H

#include <QWidget>

namespace Ui {
class Tank_10s;
}

class Tank_10s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_10s(QWidget *parent = nullptr);
    ~Tank_10s();

private:
    Ui::Tank_10s *ui;
};

#endif // TANK_10S_H
