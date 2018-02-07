#ifndef TAG_H
#define TAG_H
#include<QGraphicsRectItem>
#include"MonData.h"
class mon;
class Bar;
class Tag:public QGraphicsRectItem
{
public:
    Tag(class monInBattle *Mdefault);
//attributes
    QGraphicsTextItem tag_Name;
    QGraphicsTextItem tag_Level;
    QGraphicsTextItem tag_Exp;
    QGraphicsTextItem tag_HP;
    QGraphicsTextItem tag_MP;
    Bar* tag_HPbar;
    Bar* tag_MPbar;
    Bar* tag_Expbar;
    QGraphicsTextItem tag_Skill1;
    QGraphicsTextItem tag_Skill2;
    QGraphicsTextItem tag_description;
    QGraphicsPixmapItem tag_PixmapItem;
    monInBattle* tag_MIB;
//momber function
    void tag_update();
    void setAllPos();
private:
};


#endif // TAG_H
