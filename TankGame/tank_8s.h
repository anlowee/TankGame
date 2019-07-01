#ifndef TANK_8S_H
#define TANK_8S_H

#include <QWidget>

namespace Ui {
class Tank_8s;
}

class Tank_8s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_8s(QWidget *parent = nullptr);
    ~Tank_8s();

private:
    Ui::Tank_8s *ui;
};

#endif // TANK_8S_H
