#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QtDebug>
#include <QRect>
#include <QKeyEvent>
#include "base.h"
#define PICWIDTH 32
#define PICHEIGHT 32
#define CELLWIDTH 32
#define CELLHEIGHT 32
#define INUM 32 //line
#define JNUM 32 //row

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QWidget, protected Base
{
    Q_OBJECT

public:
    explicit DisplayWindow(QWidget *parent = nullptr);
    ~DisplayWindow();
    static int keyValue;

private:
    Ui::DisplayWindow *ui;
    void paintEvent(QPaintEvent *event);
    void PaintMap(QPainter &p);
    void MoveBullet(QPainter &p);
    void MoveTank(QPainter &p);

protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // DISPLAYWINDOW_H
