#include "TankGame.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QElapsedTimer>
#include <QDebug>
#include <QDateTime>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QPixmap pixmap("endui.jpg");
	QSplashScreen screen(pixmap);
	screen.show();
	
	//start
	screen.showMessage(QStringLiteral("Loding……"), Qt::AlignHCenter | Qt::AlignBottom, Qt::white);
	QDateTime n = QDateTime::currentDateTime();

	QDateTime now;
	do {
		now = QDateTime::currentDateTime();
	} while (n.secsTo(now) <= 3);

	TankGame w;
	w.show();

	screen.finish(&w);

	return a.exec();
}
