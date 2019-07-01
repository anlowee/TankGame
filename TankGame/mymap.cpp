#include "mymap.h"
#include <QTime>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "displaywindow.h"
#include "myglobal.h"
#include "diamondsquare.h"

char MyGlobal::logicMap[1005][1005];
bool MyGlobal::boolMap[1005][1005];
int MyGlobal::objMap[1005][1005];
int MyGlobal::dfsMap[1005][1005];
int MyGlobal::m_TrueBlockMark;

MyMap::MyMap(QObject *parent) : QObject(parent)
{
    qsrand(time(NULL));
}

double ** gen_table(int factor)
{
    int size = factor;

    double ** map = new double *[size];
    for(int i = 0; i < size; i++)
    {
        map[i] = new double[size];
        for(int j = 0; j < size; j++)
            map[i][j] = 0.0;
    }
    return map;
}

void DFS(int x, int y, int cnt, int &num)
{
    if (MyGlobal::dfsMap[x][y] > 0 || !MyGlobal::boolMap[x][y])
        return ;

    MyGlobal::dfsMap[x][y] = cnt;
    num++;
    //up
    if (x - 1 >= 0)
        DFS(x - 1, y, cnt, num);
    //down
    if (x + 1 < INUM)
        DFS(x + 1, y, cnt, num);
    //left
    if (y - 1 >= 0)
        DFS(x, y - 1, cnt, num);
    //right
    if (y + 1 < JNUM)
        DFS(x, y + 1, cnt, num);
}

void MyMap::CreateMap()
{
    int n = 5;
    int size = pow(2, n) + 1;

    double ** map1 = gen_table(size);

    DiamondSquare ds(map1, size);
    double ** map = ds.process();

    for (int i = 0; i < INUM; i++)
        for (int j = 0; j < JNUM; j++)
        {

            int n = round(map[i][j]);
            n %= 3;
            //0-Marsh-M
            //1-Rock-R
            //2-Grass-G
            switch (n)
            {
                case 0:MyGlobal::logicMap[i][j] = 'M'; MyGlobal::boolMap[i][j] = true; break;
                case 1:MyGlobal::logicMap[i][j] = 'R'; MyGlobal::boolMap[i][j] = false; break;
                case 2:MyGlobal::logicMap[i][j] = 'G'; MyGlobal::boolMap[i][j] = true; break;
                default:MyGlobal::logicMap[i][j] = 'G'; MyGlobal::boolMap[i][j] = true;
            }

            //0-nothing
            //1-blood
            //2-coin
            //3-factory
            MyGlobal::objMap[i][j] = 0;
        }

    //pre
    for (int i = 0; i < INUM; i++)
        for (int j = 0; j < JNUM; j++)
            MyGlobal::dfsMap[i][j] = 0;
    int cnt = 0, num, maxMark = 1, maxNum = 0;

    //dfs
    for (int i = 0; i < INUM; i++)
        for (int j = 0 ; j < JNUM; j++)
        {
            if (MyGlobal::dfsMap[i][j] > 0 || !MyGlobal::boolMap[i][j])
                continue;
            cnt++;
            num = 0;
            DFS(i, j, cnt, num);
            if (num > maxNum)
            {
                maxNum = num;
                maxMark = cnt;
            }
        }
    MyGlobal::m_TrueBlockMark = maxMark;
}
