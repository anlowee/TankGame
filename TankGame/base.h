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
    bool IsDisappear() {return m_bDisappear;}
    bool IsCollide(const Base &base)const;
    void SetDisappear(bool tmp) {m_bDisappear = tmp;}
    int GetPosX() {return m_pos.x();}
    int GetPosY() {return m_pos.y();}
    void SetPos(int x, int y);
    int GetDir() {return m_dir;}
    void SetDir(int dir) {m_dir = dir;}

protected:
    QPoint m_pos;
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
