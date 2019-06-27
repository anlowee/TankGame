#ifndef TANK_REINFORCE_H
#define TANK_REINFORCE_H

#include <QWidget>

namespace Ui {
class Tank_reinforce;
}

class Tank_reinforce : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_reinforce(QWidget *parent = nullptr);
    ~Tank_reinforce();

private:
    Ui::Tank_reinforce *ui;
};

#endif // TANK_REINFORCE_H
