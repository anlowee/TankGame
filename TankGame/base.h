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
    QPoint GetPos() {return m_pos;}

protected:
    QPoint m_pos;
    QRect m_rectSphere;//used to judge iscollide
    Dir m_dir;
    bool m_bDisappear;//dead then disappear
    int m_step;
    double m_health;
    double m_armor;
    double m_atk;
    double m_def;

};

#endif // BASE_H
