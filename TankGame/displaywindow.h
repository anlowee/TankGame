#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QtDebug>
#include <QRect>
#include <QKeyEvent>
#include <QTime>
#include "base.h"
#define PICWIDTH 32
#define PICHEIGHT 32
#define CELLWIDTH 32
#define CELLHEIGHT 32
#define INUM 24 //line
#define JNUM 24 //row
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
    int cntBullets;
    int cntEnemy;
    int cntKill;
    bool b_isPlayerStart;
    bool b_isPlayer2Start;
    static bool b_isTPM;
    void closeEvent(QCloseEvent * event);
signals:
    void Exit();

private:
    Ui::DisplayWindow *ui;
    void paintEvent(QPaintEvent *event);
    void PaintMap(QPainter &p);
    void MoveBullet(QPainter &p);
    void MoveTank(QPainter &p);
    void MoveTank2P(QPainter &p);
    void MoveEnemyTank(QPainter &p);
    QDateTime NextSpawnTime;

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void EnemyAtk();
    void PlayerAtk();
    void Player2Atk();
    void EnemyCreate();
};

#endif // DISPLAYWINDOW_H
