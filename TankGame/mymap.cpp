#include "mymap.h"
#include <QTime>
#include <iostream>
#include "displaywindow.h"
#include "myglobal.h"

char MyGlobal::logicMap[1005][1005];
bool MyGlobal::boolMap[1005][1005];

MyMap::MyMap(QObject *parent) : QObject(parent)
{

}

void MyMap::CreateMap()
{
    int seed = 0;
    for (int i = 0; i < INUM; i++)
        for (int j = 0; j < JNUM; j++)
        {
            qsrand((++seed)*time(NULL));
            int n = qrand()%6;
            //0-Grass-G
            //1-Tree-T
            //2-Snow-S
            //3-Marsh-M
            //4-Rock-R
            //5-Water-W
            switch (n)
            {
                case 0:MyGlobal::logicMap[i][j] = 'G'; MyGlobal::boolMap[i][j] = true; break;
                case 1:MyGlobal::logicMap[i][j] = 'T'; MyGlobal::boolMap[i][j] = true; break;
                case 2:MyGlobal::logicMap[i][j] = 'S'; MyGlobal::boolMap[i][j] = true; break;
                case 3:MyGlobal::logicMap[i][j] = 'M'; MyGlobal::boolMap[i][j] = true; break;
                case 4:MyGlobal::logicMap[i][j] = 'R'; MyGlobal::boolMap[i][j] = false; break;
                case 5:MyGlobal::logicMap[i][j] = 'W'; MyGlobal::boolMap[i][j] = false; break;
                default:MyGlobal::logicMap[i][j] = 'G'; MyGlobal::boolMap[i][j] = true;
            }
        }
}
