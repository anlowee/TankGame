#include "myglobal.h"
#include "myplayer.h"

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
    MyGlobal::configIni->setValue("Player/PlayerMaxHealth", MyPlayer::plyMaxHlt);
    MyGlobal::configIni->setValue("Player/TankForm", MyPlayer::tankForm);
}
