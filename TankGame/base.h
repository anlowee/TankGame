#ifndef BASE_H
#define BASE_H
#include <QPoint>
#include <QRect>
#include <QPainter>

enum Dir {UP, DOWN, LEFT, RIGHT};

class Base
{
public:
    Base();
    Base(int x, int y, int dir);
    bool IsDisappear() {return m_bDisappear;}
    bool IsCollide(const Base &base)const;
    void SetDisappear(bool tmp) {m_bDisappear = tmp;}
    void SetPos(int x, int y);
    int GetDir() {return m_dir;}
    int GetX() {return m_x;}
    int GetY() {return m_y;}
    void SetDir(int dir) {m_dir = dir;}
    void SetX(int x) {m_x = x;}
    void SetY(int y) {m_y = y;}

protected:
    int m_x;
    int m_y;
    QRect m_rectSphere;//used to judge iscollide
    int m_dir;
    bool m_bDisappear;//dead then disappear
    int m_step;
    double m_health;
    double m_armor;
    double m_atk;
    double m_def;

};

#endif // BASE_H
