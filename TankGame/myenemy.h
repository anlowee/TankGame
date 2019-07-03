#ifndef MYENEMY_H
#define MYENEMY_H
#include "mytank.h"
#include "mybag.h"

class MyEnemy:public MyTank, public MyBag
{
public:
    MyEnemy();
    QImage imgTankUp;
    QImage imgTankDown;
    QImage imgTankLeft;
    QImage imgTankRight;
    int tankType;
    void SetMaxHlt(double x) {m_maxHlt = x;}
    double GetMaxHlt() {return m_maxHlt;}

protected:
    double m_maxHlt;

};

#endif // MYENEMY_H
