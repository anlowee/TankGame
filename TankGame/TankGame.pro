#-------------------------------------------------
#
# Project created by QtCreator 2019-06-25T21:47:47
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TankGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        High.cpp \
        base.cpp \
        diamondsquare.cpp \
        displaywindow.cpp \
        level_1.cpp \
        level_2.cpp \
        level_3.cpp \
        level_4.cpp \
        level_5.cpp \
        main.cpp \
        mainwindow.cpp \
        mybag.cpp \
        mybullet.cpp \
        myenemy.cpp \
        myglobal.cpp \
        mymap.cpp \
        myplayer.cpp \
        mytank.cpp \
        number_1.cpp \
        number_2.cpp \
        number_3.cpp \
        number_4.cpp \
        number_5.cpp \
        readmewindow.cpp \
        recover_1.cpp \
        recover_2.cpp \
        selectlevelwindow.cpp \
        shop.cpp \
        tank_1.cpp \
        tank_10.cpp \
        tank_10s.cpp \
        tank_11.cpp \
        tank_11s.cpp \
        tank_12.cpp \
        tank_12s.cpp \
        tank_1s.cpp \
        tank_2.cpp \
        tank_2s.cpp \
        tank_3.cpp \
        tank_3s.cpp \
        tank_4.cpp \
        tank_4s.cpp \
        tank_5.cpp \
        tank_5s.cpp \
        tank_6.cpp \
        tank_6s.cpp \
        tank_7.cpp \
        tank_7s.cpp \
        tank_8.cpp \
        tank_8s.cpp \
        tank_9.cpp \
        tank_9s.cpp \
        tank_budget.cpp \
        tank_reinforce.cpp

HEADERS += \
        High.h \
        base.h \
        diamondsquare.h \
        displaywindow.h \
        level_1.h \
        level_2.h \
        level_3.h \
        level_4.h \
        level_5.h \
        mainwindow.h \
        mybag.h \
        mybullet.h \
        myenemy.h \
        myglobal.h \
        mymap.h \
        myplayer.h \
        mytank.h \
        number_1.h \
        number_2.h \
        number_3.h \
        number_4.h \
        number_5.h \
        readmewindow.h \
        recover_1.h \
        recover_2.h \
        selectlevelwindow.h \
        shop.h \
        tank_1.h \
        tank_10.h \
        tank_10s.h \
        tank_11.h \
        tank_11s.h \
        tank_12.h \
        tank_12s.h \
        tank_1s.h \
        tank_2.h \
        tank_2s.h \
        tank_3.h \
        tank_3s.h \
        tank_4.h \
        tank_4s.h \
        tank_5.h \
        tank_5s.h \
        tank_6.h \
        tank_6s.h \
        tank_7.h \
        tank_7s.h \
        tank_8.h \
        tank_8s.h \
        tank_9.h \
        tank_9s.h \
        tank_budget.h \
        tank_reinforce.h

FORMS += \
        High.ui \
        displaywindow.ui \
        level_1.ui \
        level_2.ui \
        level_3.ui \
        level_4.ui \
        level_5.ui \
        mainwindow.ui \
        number_1.ui \
        number_2.ui \
        number_3.ui \
        number_4.ui \
        number_5.ui \
        readmewindow.ui \
        recover_1.ui \
        recover_2.ui \
        selectlevelwindow.ui \
        shop.ui \
        tank_1.ui \
        tank_10.ui \
        tank_10s.ui \
        tank_11.ui \
        tank_11s.ui \
        tank_12.ui \
        tank_12s.ui \
        tank_1s.ui \
        tank_2.ui \
        tank_2s.ui \
        tank_3.ui \
        tank_3s.ui \
        tank_4.ui \
        tank_4s.ui \
        tank_5.ui \
        tank_5s.ui \
        tank_6.ui \
        tank_6s.ui \
        tank_7.ui \
        tank_7s.ui \
        tank_8.ui \
        tank_8s.ui \
        tank_9.ui \
        tank_9s.ui \
        tank_budget.ui \
        tank_reinforce.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
<<<<<<< HEAD
    Shop_defence.jpg \
    Shop_defence_plus.jpg \
    Shop_faster.jpg \
    Shop_faster_plus.jpg \
    Shop_recover.jpg \
    Shop_recover1.jpg \
    Shop_reinforce.jpg \
    Shop_reinforce_plus.jpg
=======
    ../build-TankGame-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/tank1down.png \
    ../build-TankGame-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/tank1left.png \
    ../build-TankGame-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/tank1right.png \
    ../build-TankGame-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/tank1up.png
>>>>>>> d94c4bb842a5bce43961b2a04a0ac0486702e7ea
