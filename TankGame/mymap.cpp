#include "mymap.h"
#include <QTime>
#include <iostream>
#define WID 10
#define LEN 10

MyMap::MyMap(QObject *parent) : QObject(parent)
{

}

void MyMap::CreateMap()
{
    int seed = 0;
    for (int i = 0; i < WID; i++)
        for (int j = 0; j < LEN; j++)
        {
            qsrand((++seed)*time(NULL));
            int n = qrand()%7;
            //0-Grass-G
            //1-Tree-T
            //2-Snow-S
            //3-Marsh-M
            //4-Rock-R
            //5-Water-W
            //6-Factory-F
            switch (n)
            {
                case 0:logicMap[i][j] = 'G'; break;
                case 1:logicMap[i][j] = 'T'; break;
                case 2:logicMap[i][j] = 'S'; break;
                case 3:logicMap[i][j] = 'M'; break;
                case 4:logicMap[i][j] = 'R'; break;
                case 5:logicMap[i][j] = 'W'; break;
                case 6:logicMap[i][j] = 'F'; break;
                default:logicMap[i][j] = 'G';
            }
        }
}

void MyMap::DrawMap()
{
    for (int i = 0; i < WID; i++)
    {
        for (int j = 0; j < LEN; j++)
            std::cout << logicMap[i][j] << " ";
        std::cout << std::endl;
    }
}
