#ifndef ATTACK_1_H
#define ATTACK_1_H

#include <QWidget>

namespace Ui {
class Attack_1;
}

class Attack_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Attack_1(QWidget *parent = nullptr);
    ~Attack_1();

private:
    Ui::Attack_1 *ui;
};

#endif // ATTACK_1_H
