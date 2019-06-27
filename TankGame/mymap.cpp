#include "mymap.h"
#include <QTime>
#include <iostream>
#include "displaywindow.h"
#include "myglobal.h"

char MyGlobal::logicMap[1005][1005];

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
            //6-Factory-F
            switch (n)
            {
                case 0:MyGlobal::logicMap[i][j] = 'G'; break;
                case 1:MyGlobal::logicMap[i][j] = 'T'; break;
                case 2:MyGlobal::logicMap[i][j] = 'S'; break;
                case 3:MyGlobal::logicMap[i][j] = 'M'; break;
                case 4:MyGlobal::logicMap[i][j] = 'R'; break;
                case 5:MyGlobal::logicMap[i][j] = 'W'; break;
                default:MyGlobal::logicMap[i][j] = 'G';
            }
        }
}
