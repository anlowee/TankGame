#include "myenemy.h"

double MyEnemy::getHealth(){
    return m_health;
}
int MyEnemy::addMoney(){
    if(m_health==0.0){
        int myMoney=0;
        myMoney=MyBag::addMoney();
        return myMoney;
    }

}
