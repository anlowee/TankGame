#ifndef TANK_12S_H
#define TANK_12S_H

#include <QWidget>

namespace Ui {
class Tank_12s;
}

class Tank_12s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_12s(QWidget *parent = nullptr);
    ~Tank_12s();

private:
    Ui::Tank_12s *ui;
};

#endif // TANK_12S_H
