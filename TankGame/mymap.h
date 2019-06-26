#ifndef MYMAP_H
#define MYMAP_H

#include <QObject>
#include <QWidget>

class MyMap : public QObject
{
    Q_OBJECT
public:
    explicit MyMap(QObject *parent = nullptr);
    char logicMap[1005][1005];
    void CreateMap();
    void DrawMap();

signals:

public slots:
};

#endif // MYMAP_H
