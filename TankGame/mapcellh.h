#ifndef MAPCELLH_H
#define MAPCELLH_H
#ifndef MAPCELL_H
#define MAPCELL_H

#include"wanwu.h"
#include"main.h"
#include<fstream>
class Mapcell : public Wanwu
{
public:

    Mapcell();
    Mapcell(int iIndex,int jIndex,int style=0,float life=200){


        this->m_pos.setX(jIndex*CELLWIDTH+CELLWIDTH/2);
        this->m_pos.setY(iIndex*CELLHEIGHT+CELLHEIGHT/2);
        this->CalculateSphere();
        this->m_bDisappear=false;
        this->life=life;
        this->style=style%28;//map_block.png总共有28小块

    }
    // 绘图
    void Display(QPainter &paint);

    // 移动
   void Move();
   //得到方块样式
   int getstyle(){return style;}
   //切换样式
   int switchstyle(){style++;style=style%28;return style;}
   //设置样式
   void setstyle(int style){this->style=style;}


private:
//static QImage blockimage;
   int style;//方块样式，从图片上依次编号0 ，1，2 ，3，4，5.。。。。
   //
   void cal(int style,int &i,int &j){//将一维编号变成一行有4列的二维编号i行j列
     i=style/4;
    j=style%4;
   }
void CalculateSphere(){
    this->m_rectSphere.setRect(m_pos.x()-CELLWIDTH/2,m_pos.y()-CELLHEIGHT/2,CELLWIDTH,CELLHEIGHT);

}


};
#endif // MAPCELL_H
class mapcellh
{
public:
    mapcellh();
};

#endif // MAPCELLH_H
