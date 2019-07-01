#ifndef MYENEMY_H
#define MYENEMY_H
#include "mytank.h"
#include "mybag.h"

class MyEnemy:public MyTank, public MyBag
{
public:
    MyEnemy();
double getHealth();
int addMoney();
protected:

};

#endif // MYENEMY_H
