#ifndef MYENEMY_H
#define MYENEMY_H
#include "mytank.h"
#include "mybag.h"

class MyEnemy:protected MyTank, protected MyBag
{
public:
    MyEnemy();

protected:

};

#endif // MYENEMY_H
