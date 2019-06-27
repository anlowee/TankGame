#ifndef MYTANK_H
#define MYTANK_H
#include "base.h"

class MyTank:protected Base
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
