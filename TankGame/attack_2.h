#ifndef ATTACK_2_H
#define ATTACK_2_H

#include <QWidget>

namespace Ui {
class Attack_2;
}

class Attack_2 : public QWidget
{
    Q_OBJECT

public:
    explicit Attack_2(QWidget *parent = nullptr);
    ~Attack_2();

private:
    Ui::Attack_2 *ui;
};

#endif // ATTACK_2_H
