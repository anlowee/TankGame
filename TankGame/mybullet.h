#ifndef MYBULLET_H
#define MYBULLET_H
#include "base.h"
#define BULLETSPEED 10

class MyBullet:public Base
{
public:
    MyBullet();
    MyBullet(int x, int y, int dir);

protected:
    int m_bulletForm;//choose one of outlooks
};

#endif // MYBULLET_H
