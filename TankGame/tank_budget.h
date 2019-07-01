#ifndef TANK_BUDGET_H
#define TANK_BUDGET_H

#include <QWidget>
#include <QImage>
#include <QStackedWidget>
#include "recover_1.h"
#include "recover_2.h"
#include "tank_1.h"
#include "tank_10.h"
#include "tank_11.h"
#include "tank_12.h"
#include "tank_2.h"
#include "tank_3.h"
#include "tank_4.h"
#include "tank_5.h"
#include "tank_6.h"
#include "tank_7.h"
#include "tank_8.h"
#include "tank_9.h"
#include "tank_1s.h"
#include "tank_10s.h"
#include "tank_11s.h"
#include "tank_12s.h"
#include "tank_2s.h"
#include "tank_3s.h"
#include "tank_4s.h"
#include "tank_5s.h"
#include "tank_6s.h"
#include "tank_7s.h"
#include "tank_8s.h"
#include "tank_9s.h"
namespace Ui {
class Tank_budget;
}

class Tank_budget : public QWidget
{
    Q_OBJECT

public:
    explicit Tank_budget(QWidget *parent = nullptr);
    ~Tank_budget();

private slots:
    void on_backButton_clicked();

    void on_recoverButton_clicked();

    void on_levelUpButton_clicked();

private:
    Ui::Tank_budget *ui;
    Recover_1 *a;
    Recover_2 *b;
    int i = 1;
    Tank_1 *c1;
    Tank_2 *c2;
    Tank_3 *c3;
    Tank_4 *c4;
    Tank_5 *c5;
    Tank_6 *c6;
    Tank_7 *c7;
    Tank_8 *c8;
    Tank_9 *c9;
    Tank_10 *c10;
    Tank_11 *c11;
    Tank_12 *c12;
    int j = 1;
    Tank_1s *d1;
    Tank_2s *d2;
    Tank_3s *d3;
    Tank_4s *d4;
    Tank_5s *d5;
    Tank_6s *d6;
    Tank_7s *d7;
    Tank_8s *d8;
    Tank_9s *d9;
    Tank_10s *d10;
    Tank_11s *d11;
    Tank_12s *d12;
};

#endif // TANK_BUDGET_H
