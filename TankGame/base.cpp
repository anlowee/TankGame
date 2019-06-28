#include "base.h"

Base::Base()
{

}

Base::Base(int x, int y, int dir):m_x(x), m_y(y), m_dir(dir)
{

}

bool Base::IsCollide(const Base &base) const
{
    bool bisCollide = true;
    if (base.m_rectSphere.left() > m_rectSphere.right()
            || base.m_rectSphere.right() < m_rectSphere.left()
            || base.m_rectSphere.top() > m_rectSphere.bottom()
            || base.m_rectSphere.bottom() < m_rectSphere.top())
        bisCollide = false;

    //true-collide
    //false-not collide
    return bisCollide;
}
