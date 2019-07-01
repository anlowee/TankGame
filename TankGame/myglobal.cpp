#include "myglobal.h"

QSettings* MyGlobal::configIni = new QSettings("save.sav", QSettings::IniFormat);;

MyGlobal::MyGlobal()
{

}
