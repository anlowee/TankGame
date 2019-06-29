#ifndef MYTANK_H
#define MYTANK_H
#include "base.h"
#define NORMALSPEED 5
#define ENEMYSPEED 1
#define PLAYERLIFE 100.0
#define ENEMYLIFE 60.0
#define PLAYERATK 30.0
#define ENEMYATK 30.0
#define PLAYERDEF 5.0
#define ENEMYDEF 5.0

class MyTank:public Base
{
public:
    MyTank();

protected:
    bool m_bisSpeedBuff;
    bool m_bisAtkBuff;
    bool m_bisDefBuff;
    int m_tankForm;//choose one of outlooks
};

#endif // MYTANK_H
