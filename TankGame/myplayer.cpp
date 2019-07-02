#include "myplayer.h"

int MyPlayer::plyX;
int MyPlayer::plyY;
int MyPlayer::plyD;
int MyPlayer::plyMoney;
int MyPlayer::plySpeed;
int MyPlayer::plyKill;
int MyPlayer::ply2X;
int MyPlayer::ply2Y;
int MyPlayer::ply2D;
int MyPlayer::ply2Money;
int MyPlayer::ply2Kill;
int MyPlayer::tankForm;
int MyPlayer::plyAtkSpeed;
double MyPlayer::plyAtk;
double MyPlayer::plyDef;
double MyPlayer::plyHlt;
double MyPlayer::plyMaxHlt;
double MyPlayer::ply2Atk;
double MyPlayer::ply2Def;
double MyPlayer::ply2Hlt;
QImage MyPlayer::imgTankUp;
QImage MyPlayer::imgTankDown;
QImage MyPlayer::imgTankLeft;
QImage MyPlayer::imgTankRight;
QImage MyPlayer::imgHealth;

MyPlayer::MyPlayer()
{

}

void MyPlayer::LoadImg()
{
    int tf = tankForm;
    //load player tank img
    QImage imgTank1Up("tank1up.png");
    QImage imgTank1Down("tank1down.png");
    QImage imgTank1Left("tank1left.png");
    QImage imgTank1Right("tank1right.png");

    MyPlayer::imgTankUp = imgTank1Up;
    MyPlayer::imgTankDown = imgTank1Down;
    MyPlayer::imgTankLeft = imgTank1Left;
    MyPlayer::imgTankRight = imgTank1Right;

    if (tf == 2)
    {
        QImage imgTank2Up("tank2up.png");
        QImage imgTank2Down("tank2down.png");
        QImage imgTank2Left("tank2left.png");
        QImage imgTank2Right("tank2right.png");

        MyPlayer::imgTankUp = imgTank2Up;
        MyPlayer::imgTankDown = imgTank2Down;
        MyPlayer::imgTankLeft = imgTank2Left;
        MyPlayer::imgTankRight = imgTank2Right;
    }
    if (tf == 3)
    {
        QImage imgTank3Up("tank3up.png");
        QImage imgTank3Down("tank3down.png");
        QImage imgTank3Left("tank3left.png");
        QImage imgTank3Right("tank3right.png");

        MyPlayer::imgTankUp = imgTank3Up;
        MyPlayer::imgTankDown = imgTank3Down;
        MyPlayer::imgTankLeft = imgTank3Left;
        MyPlayer::imgTankRight = imgTank3Right;
    }
    if (tf == 4)
    {
        QImage imgTank4Up("tank4up.png");
        QImage imgTank4Down("tank4down.png");
        QImage imgTank4Left("tank4left.png");
        QImage imgTank4Right("tank4right.png");

        MyPlayer::imgTankUp = imgTank4Up;
        MyPlayer::imgTankDown = imgTank4Down;
        MyPlayer::imgTankLeft = imgTank4Left;
        MyPlayer::imgTankRight = imgTank4Right;
    }
    if (tf == 5)
    {
        QImage imgTank5Up("tank5up.png");
        QImage imgTank5Down("tank5down.png");
        QImage imgTank5Left("tank5left.png");
        QImage imgTank5Right("tank5right.png");

        MyPlayer::imgTankUp = imgTank5Up;
        MyPlayer::imgTankDown = imgTank5Down;
        MyPlayer::imgTankLeft = imgTank5Left;
        MyPlayer::imgTankRight = imgTank5Right;
    }
    if (tf == 6)
    {
        QImage imgTank6Up("tank6up.png");
        QImage imgTank6Down("tank6down.png");
        QImage imgTank6Left("tank6left.png");
        QImage imgTank6Right("tank6right.png");

        MyPlayer::imgTankUp = imgTank6Up;
        MyPlayer::imgTankDown = imgTank6Down;
        MyPlayer::imgTankLeft = imgTank6Left;
        MyPlayer::imgTankRight = imgTank6Right;
    }
    if (tf == 7)
    {
        QImage imgTank7Up("tank7up.png");
        QImage imgTank7Down("tank7down.png");
        QImage imgTank7Left("tank7left.png");
        QImage imgTank7Right("tank7right.png");

        MyPlayer::imgTankUp = imgTank7Up;
        MyPlayer::imgTankDown = imgTank7Down;
        MyPlayer::imgTankLeft = imgTank7Left;
        MyPlayer::imgTankRight = imgTank7Right;
    }
    if (tf == 8)
    {
        QImage imgTank8Up("tank8up.png");
        QImage imgTank8Down("tank8down.png");
        QImage imgTank8Left("tank8left.png");
        QImage imgTank8Right("tank8right.png");

        MyPlayer::imgTankUp = imgTank8Up;
        MyPlayer::imgTankDown = imgTank8Down;
        MyPlayer::imgTankLeft = imgTank8Left;
        MyPlayer::imgTankRight = imgTank8Right;
    }
    if (tf == 9)
    {
        QImage imgTank9Up("tank9up.png");
        QImage imgTank9Down("tank9down.png");
        QImage imgTank9Left("tank9left.png");
        QImage imgTank9Right("tank9right.png");

        MyPlayer::imgTankUp = imgTank9Up;
        MyPlayer::imgTankDown = imgTank9Down;
        MyPlayer::imgTankLeft = imgTank9Left;
        MyPlayer::imgTankRight = imgTank9Right;
    }
    if (tf == 10)
    {
        QImage imgTank10Up("tank10up.png");
        QImage imgTank10Down("tank10down.png");
        QImage imgTank10Left("tank10left.png");
        QImage imgTank10Right("tank10right.png");

        MyPlayer::imgTankUp = imgTank10Up;
        MyPlayer::imgTankDown = imgTank10Down;
        MyPlayer::imgTankLeft = imgTank10Left;
        MyPlayer::imgTankRight = imgTank10Right;
    }
    if (tf == 11)
    {
        QImage imgTank11Up("tank11up.png");
        QImage imgTank11Down("tank11down.png");
        QImage imgTank11Left("tank11left.png");
        QImage imgTank11Right("tank11right.png");

        MyPlayer::imgTankUp = imgTank11Up;
        MyPlayer::imgTankDown = imgTank11Down;
        MyPlayer::imgTankLeft = imgTank11Left;
        MyPlayer::imgTankRight = imgTank11Right;
    }
    if (tf == 12)
    {
        QImage imgTank12Up("tank12up.png");
        QImage imgTank12Down("tank12down.png");
        QImage imgTank12Left("tank12left.png");
        QImage imgTank12Right("tank12right.png");

        MyPlayer::imgTankUp = imgTank12Up;
        MyPlayer::imgTankDown = imgTank12Down;
        MyPlayer::imgTankLeft = imgTank12Left;
        MyPlayer::imgTankRight = imgTank12Right;
    }

    QImage imgHealth("life.png");
    MyPlayer::imgHealth = imgHealth;
}
