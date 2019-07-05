#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QPixmap pixmap("startPre.jpg");
    QSplashScreen screen(pixmap);
    screen.show();
    screen.showMessage("LOADING...", Qt::AlignCenter, Qt::black);

    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
        app.processEvents();
    } while (n.secsTo(now)<=1);

    MainWindow w;
    w.show();

    screen.finish(&w);

    return app.exec();
}
