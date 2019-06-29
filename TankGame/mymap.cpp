#include "mymap.h"
#include <QTime>
#include <iostream>
#include "displaywindow.h"
#include "myglobal.h"

char MyGlobal::logicMap[1005][1005];
bool MyGlobal::boolMap[1005][1005];
int MyGlobal::objMap[1005][1005];

MyMap::MyMap(QObject *parent) : QObject(parent)
{
    qsrand(time(NULL));
}

void MyMap::CreateMap()
{
    for (int i = 0; i < INUM; i++)
        for (int j = 0; j < JNUM; j++)
        {
            /*
            int n = qrand()%2;
            //0-Grass-G
            //1-Rock-R
            switch (n)
            {
                case 0:MyGlobal::logicMap[i][j] = 'G'; MyGlobal::boolMap[i][j] = true; break;
                case 1:MyGlobal::logicMap[i][j] = 'R'; MyGlobal::boolMap[i][j] = false; break;
                default:MyGlobal::logicMap[i][j] = 'G'; MyGlobal::boolMap[i][j] = true;
            }
            */
            MyGlobal::logicMap[i][j] = 'G';
            MyGlobal::boolMap[i][j] = true;
            //0-nothing
            //1-blood
            //2-coin
            MyGlobal::objMap[i][j] = 0;
        }
}
