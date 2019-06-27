#-------------------------------------------------
#
# Project created by QtCreator 2019-06-25T21:47:47
#
#-------------------------------------------------

QT       += core gui

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
        selectlevelwindow.cpp \
        shop.cpp \
        tank_budget.cpp \
        tank_reinforce.cpp

HEADERS += \
        High.h \
        base.h \
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
        selectlevelwindow.h \
        shop.h \
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
        selectlevelwindow.ui \
        shop.ui \
        tank_budget.ui \
        tank_reinforce.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES +=
