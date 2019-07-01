#ifndef TANK_1S_H
#define TANK_1S_H

#include <QWidget>

namespace Ui {
class Tank_1s;
}

class Tank_1s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_1s(QWidget *parent = nullptr);
    ~Tank_1s();

private:
    Ui::Tank_1s *ui;
};

#endif // TANK_1S_H
