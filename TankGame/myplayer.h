#ifndef MYPLAYER_H
#define MYPLAYER_H
#include "mytank.h"
#include "mybag.h"

class MyPlayer:protected MyTank, protected MyBag
{
public:
    MyPlayer();

protected:

};

#endif // MYPLAYER_H
