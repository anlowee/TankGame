#ifndef MYTANK_H
#define MYTANK_H
#include "base.h"
#define NORMALSPEED 3

class MyTank:public Base
{
public:
    MyTank();

protected:
    bool m_bisSpeedBuff;
    bool m_bisAtkBuff;
    bool m_bisDefBuff;
    int m_atkSpeed;
    int m_tankForm;//choose one of outlooks
};

#endif // MYTANK_H
