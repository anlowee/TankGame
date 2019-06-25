#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TankGame.h"

class TankGame : public QMainWindow
{
	Q_OBJECT

public:
	TankGame(QWidget *parent = Q_NULLPTR);

private:
	Ui::TankGameClass ui;
};
