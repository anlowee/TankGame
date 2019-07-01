#ifndef MYGLOBAL_H
#define MYGLOBAL_H

#include <QSettings>
class MyGlobal
{
public:
    MyGlobal();
    static char logicMap[1005][1005];
    static bool boolMap[1005][1005];
    static int objMap[1005][1005];
    static int dfsMap[1005][1005];
    static int m_TrueBlockMark;
    static QSettings* configIni;
};

#endif // MYGLOBAL_H
