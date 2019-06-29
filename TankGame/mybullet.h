#ifndef MYBULLET_H
#define MYBULLET_H
#include "base.h"
#define BULLETSPEED 5
#define BULLETWIDTH 16
#define BULLETHEIGHT 16

class MyBullet:public Base
{
public:
    MyBullet();
    MyBullet(int x, int y, int dir);
    int GetCreator() {return m_creator;}
    void SetCreator(int x) {m_creator = x;}

protected:
    int m_bulletForm;//choose one of outlooks
    int m_creator;
};

#endif // MYBULLET_H
