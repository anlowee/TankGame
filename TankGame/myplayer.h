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
    static double plyAtk;
    static double plyDef;
    static double plyHlt;
    static double plyMaxHlt;
    static int plyMoney;
    static int plyKill;
    static int plySpeed;
    static int plyAtkSpeed;
    static int tankForm;
    static QImage imgTankUp;
    static QImage imgTankDown;
    static QImage imgTankLeft;
    static QImage imgTankRight;
    static QImage imgHealth;
    static void LoadImg();

    static int ply2X;
    static int ply2Y;
    static int ply2D;
    static double ply2Atk;
    static double ply2Def;
    static double ply2Hlt;
    static int ply2Money;
    static int ply2Kill;

private:

};

#endif // MYPLAYER_H
