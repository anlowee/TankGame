/********************************************************************************
** Form generated from reading UI file 'TankGame.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TANKGAME_H
#define UI_TANKGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TankGameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TankGameClass)
    {
        if (TankGameClass->objectName().isEmpty())
            TankGameClass->setObjectName(QString::fromUtf8("TankGameClass"));
        TankGameClass->resize(600, 400);
        menuBar = new QMenuBar(TankGameClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TankGameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TankGameClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TankGameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TankGameClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TankGameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TankGameClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TankGameClass->setStatusBar(statusBar);

        retranslateUi(TankGameClass);

        QMetaObject::connectSlotsByName(TankGameClass);
    } // setupUi

    void retranslateUi(QMainWindow *TankGameClass)
    {
        TankGameClass->setWindowTitle(QCoreApplication::translate("TankGameClass", "TankGame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TankGameClass: public Ui_TankGameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TANKGAME_H
