#ifndef MYBAG_H
#define MYBAG_H


class MyBag
{
public:
    MyBag();
    int addMoney();
    int getMedicine();
    int getResurrent();
    int mySpecialWeapon();
protected:
    //all of int is the num of sth
    int m_money;
    int m_medicine;
    int m_resurrent;
    int m_specialWeapon;
    //add more here...
};


#endif // MYBAG_H
