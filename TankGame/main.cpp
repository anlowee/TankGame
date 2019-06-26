#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString imgPath = "startPre.jpg";
    QPixmap pixmap(imgPath);
    QSplashScreen splash(pixmap);
    splash.show();

    splash.showMessage(QStringLiteral("LOADING..."), Qt::AlignHCenter|Qt::AlignBottom, Qt::black);

    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
    } while (n.secsTo(now)<=3);

    MainWindow w;
    w.show();

    splash.finish(&w);
    return a.exec();
}
