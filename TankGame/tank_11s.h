#ifndef TANK_11S_H
#define TANK_11S_H

#include <QWidget>

namespace Ui {
class Tank_11s;
}

class Tank_11s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_11s(QWidget *parent = nullptr);
    ~Tank_11s();

private:
    Ui::Tank_11s *ui;
};

#endif // TANK_11S_H
