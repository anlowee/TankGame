#ifndef TANK_REINFORCE_H
#define TANK_REINFORCE_H

#include <QWidget>
#include <QStackedWidget>
#include "attack_1.h"
#include "attack_2.h"
#include "defence_1.h"
#include "defence_2.h"
#include "fast_1.h"
#include "fast_2.h"

namespace Ui {
class Tank_reinforce;
}

class Tank_reinforce : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_reinforce(QWidget *parent = nullptr);
    ~Tank_reinforce();

private slots:
    void on_backButton_clicked();

    void on_attackButton_clicked();

    void on_defenceButton_clicked();

    void on_fastButton_clicked();

private:
    Ui::Tank_reinforce *ui;
    Attack_1 *a1;
    Attack_2 *a2;
    Defence_1 *b1;
    Defence_2 *b2;
    Fast_1 *c1;
    Fast_2 *c2;
    int i = 1;
    int j = 1;
    int k = 1;
};

#endif // TANK_REINFORCE_H
