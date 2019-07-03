#ifndef MYBULLET_H
#define MYBULLET_H
#include "base.h"
#define BULLETSPEED 10
#define BULLETWIDTH 8
#define BULLETHEIGHT 16

class MyBullet:public Base
{
public:
    MyBullet();
    MyBullet(int x, int y, int dir);
    int GetCreator() {return m_creator;}
    void SetCreator(int x) {m_creator = x;}
    int m_bulletForm;//choose one of outlooks
    void LoadImg();
    QImage imgBulletUp;
    QImage imgBulletDown;
    QImage imgBulletLeft;
    QImage imgBulletRight;

protected:
    int m_creator;
};

#endif // MYBULLET_H
