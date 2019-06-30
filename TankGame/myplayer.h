#ifndef MYPLAYER_H
#define MYPLAYER_H
#include "mytank.h"
#include "mybag.h"

class MyPlayer:public MyTank, public MyBag
{
public:
    MyPlayer();
    static int plyX;
    static int plyY;
    static int plyD;
    static bool status;
    static double plyAtk;
    static double plyDef;
    static double plyHlt;
    static int plyMoney;
    static int plyKill;

private:

};

#endif // MYPLAYER_H
