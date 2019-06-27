#ifndef MYMAP_H
#define MYMAP_H

#include <QObject>
#include <QWidget>
#include "base.h"
#include "displaywindow.h"
#include "myglobal.h"
#include <fstream>
#include <QImage>

class MyMap : public QObject, public Base, public MyGlobal
{
    Q_OBJECT
public:
    explicit MyMap(QObject *parent = nullptr);
    void CreateMap();

private:

signals:

public slots:
};

#endif // MYMAP_H
