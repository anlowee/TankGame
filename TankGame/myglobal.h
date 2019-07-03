#ifndef MYGLOBAL_H
#define MYGLOBAL_H

#include <QSettings>
#include <QImage>

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
    static void LoadMapImg();

    //map img
    static QImage imgGrass;
    static QImage imgRock;
    static QImage imgMarsh;
    static QImage imgBlood;
    static QImage imgCoin;
    static QImage imgHealth;//factory health
    static QImage imgFactory;
    static QImage imgFactoryBoom;

    //tank img
    static QImage imgTankBoom;
    static QImage img1PHlt;//1p health
    static QImage img2PHlt;//2p health
    static QImage imgEnemyHlt;
    static QImage imgBossHlt;

    //bullet1 img
    static QImage imgPlayerBulletUp;
    static QImage imgPlayerBulletDown;
    static QImage imgPlayerBulletLeft;
    static QImage imgPlayerBulletRight;

    //bullet2 img
    static QImage imgEnemyBulletUp;
    static QImage imgEnemyBulletDown;
    static QImage imgEnemyBulletLeft;
    static QImage imgEnemyBulletRight;

    //bullet3 img
    static QImage imgBossBulletUp;
    static QImage imgBossBulletDown;
    static QImage imgBossBulletLeft;
    static QImage imgBossBulletRight;

    //bullet4 img
    static QImage img2PBulletUp;
    static QImage img2PBulletDown;
    static QImage img2PBulletLeft;
    static QImage img2PBulletRight;



    static void SaveData();
};

#endif // MYGLOBAL_H
