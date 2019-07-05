#include "mybag.h"

int MyBag::addMoney(){
    m_money=m_money+10;
    return m_money;
}
int MyBag:: getMedicine(){
    m_medicine=m_medicine+1;
    return m_medicine;
}
int MyBag:: getResurrent(){
    m_resurrent=m_resurrent+1;
    return m_resurrent;
}

