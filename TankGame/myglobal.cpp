#include "myglobal.h"
#include "myplayer.h"

QImage MyGlobal::imgGrass;
QImage MyGlobal::imgRock;
QImage MyGlobal::imgMarsh;
QImage MyGlobal::imgBlood;
QImage MyGlobal::imgCoin;
QImage MyGlobal::imgHealth;
QImage MyGlobal::imgFactory;
QImage MyGlobal::imgFactoryBoom;
QImage MyGlobal::imgTankBoom;
QImage MyGlobal::img1PHlt;
QImage MyGlobal::img2PHlt;
QImage MyGlobal::imgEnemyHlt;
QImage MyGlobal::imgBossHlt;
QImage MyGlobal::imgPlayerBulletUp;
QImage MyGlobal::imgPlayerBulletDown;
QImage MyGlobal::imgPlayerBulletLeft;
QImage MyGlobal::imgPlayerBulletRight;
QImage MyGlobal::imgEnemyBulletUp;
QImage MyGlobal::imgEnemyBulletDown;
QImage MyGlobal::imgEnemyBulletLeft;
QImage MyGlobal::imgEnemyBulletRight;
QImage MyGlobal::imgBossBulletUp;
QImage MyGlobal::imgBossBulletDown;
QImage MyGlobal::imgBossBulletRight;
QImage MyGlobal::imgBossBulletLeft;
QImage MyGlobal::img2PBulletUp;
QImage MyGlobal::img2PBulletDown;
QImage MyGlobal::img2PBulletLeft;
QImage MyGlobal::img2PBulletRight;
QSettings* MyGlobal::configIni = new QSettings("save.sav", QSettings::IniFormat);;

MyGlobal::MyGlobal()
{

}

void MyGlobal::SaveData()
{
    MyGlobal::configIni->setValue("Player/Money",MyPlayer::plyMoney);
    MyGlobal::configIni->setValue("Player/Kills",MyPlayer::plyKill);
    MyGlobal::configIni->setValue("Player/PlayerATK", MyPlayer::plyAtk);
    MyGlobal::configIni->setValue("Player/PlayerDEF", MyPlayer::plyDef);
    MyGlobal::configIni->setValue("Player/Speed", MyPlayer::plySpeed);
    MyGlobal::configIni->setValue("Player/PlayerATKSpeed", MyPlayer::plyAtkSpeed);
    MyGlobal::configIni->setValue("Player/PlayerMaxHealth", MyPlayer::plyMaxHlt);
    MyGlobal::configIni->setValue("Player/TankForm", MyPlayer::tankForm);
}

void MyGlobal::LoadMapImg()
{
    //map img
    QImage imgGrass1("grass.png");
    QImage imgRock1("rock.png");
    QImage imgMarsh1("marsh.png");
    QImage imgBlood1("blood.png");
    QImage imgCoin1("coin.png");
    QImage imgFactory1("factory.png");
    QImage imgHealth1("life2.png");
    QImage imgFactoryBoom1("factoryboom.png");

    //tank img
    QImage imgTankBoom1("tankboom.png");
    QImage img1PHlt1("life.png");
    QImage img2PHlt1("life3.png");
    QImage imgEnemyHlt1("life4.png");
    QImage imgBossHlt1("life5.png");

    //bullet1 img
    QImage imgBullet1Up1("bullet1up.png");
    QImage imgBullet1Down1("bullet1down.png");
    QImage imgBullet1Left1("bullet1left.png");
    QImage imgBullet1Right1("bullet1right.png");

    //bullet2 img
    QImage imgBullet2Up1("bullet2up.png");
    QImage imgBullet2Down1("bullet2down.png");
    QImage imgBullet2Left1("bullet2left.png");
    QImage imgBullet2Right1("bullet2right.png");

    //bullet3 img
    QImage imgBullet3Up1("bullet3up.png");
    QImage imgBullet3Down1("bullet3down.png");
    QImage imgBullet3Left1("bullet3left.png");
    QImage imgBullet3Right1("bullet3right.png");

    //bullet4 img
    QImage imgBullet4Up1("bullet4up.png");
    QImage imgBullet4Down1("bullet4down.png");
    QImage imgBullet4Left1("bullet4left.png");
    QImage imgBullet4Right1("bullet4right.png");

    //map
    imgGrass = imgGrass1;
    imgRock = imgRock1;
    imgMarsh = imgMarsh1;
    imgBlood = imgBlood1;
    imgCoin = imgCoin1;
    imgHealth = imgHealth1;
    imgFactory = imgFactory1;
    imgFactoryBoom = imgFactoryBoom1;

    //tank
    imgTankBoom = imgTankBoom1;
    img1PHlt = img1PHlt1;
    img2PHlt = img2PHlt1;
    imgEnemyHlt = imgEnemyHlt1;
    imgBossHlt = imgBossHlt1;

    //bullet
    imgPlayerBulletUp = imgBullet1Up1;
    imgPlayerBulletDown = imgBullet1Down1;
    imgPlayerBulletLeft = imgBullet1Left1;
    imgPlayerBulletRight = imgBullet1Right1;

    imgEnemyBulletUp = imgBullet2Up1;
    imgEnemyBulletDown = imgBullet2Down1;
    imgEnemyBulletLeft = imgBullet2Left1;
    imgEnemyBulletRight = imgBullet2Right1;

    imgBossBulletUp = imgBullet3Up1;
    imgBossBulletDown = imgBullet3Down1;
    imgBossBulletLeft = imgBullet3Left1;
    imgBossBulletRight = imgBullet3Right1;

    img2PBulletUp = imgBullet4Up1;
    img2PBulletDown = imgBullet4Up1;
    img2PBulletLeft = imgBullet4Left1;
    img2PBulletRight = imgBullet4Right1;
}
