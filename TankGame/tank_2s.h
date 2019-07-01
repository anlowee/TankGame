#ifndef TANK_2S_H
#define TANK_2S_H

#include <QWidget>

namespace Ui {
class Tank_2s;
}

class Tank_2s : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_2s(QWidget *parent = nullptr);
    ~Tank_2s();

private:
    Ui::Tank_2s *ui;
};

#endif // TANK_2S_H
