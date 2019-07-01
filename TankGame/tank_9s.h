#ifndef TANK_9S_H
#define TANK_9S_H

#include <QWidget>

namespace Ui {
class Tank_9s;
}

class Tank_9s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_9s(QWidget *parent = nullptr);
    ~Tank_9s();

private:
    Ui::Tank_9s *ui;
};

#endif // TANK_9S_H
