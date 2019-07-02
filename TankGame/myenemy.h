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

protected:

};

#endif // MYENEMY_H
