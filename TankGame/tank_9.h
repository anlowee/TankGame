#ifndef TANK_9_H
#define TANK_9_H

#include <QWidget>

namespace Ui {
class Tank_9;
}

class Tank_9 : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_9(QWidget *parent = nullptr);
    ~Tank_9();

private:
    Ui::Tank_9 *ui;
};

#endif // TANK_9_H
