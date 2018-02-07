#ifndef BASE_H
#define BASE_H

#include"mytextitem.h"
#include"mytimer.h"
#include<QGraphicsPixmapItem>
#include<QGraphicsItem>
#include<QGraphicsSceneMouseEvent>
#include<QObject>

class Wall: public QGraphicsPixmapItem
{
public:
    Wall(QGraphicsItem *parent=0);

};

class Grass:public QObject,public QGraphicsPixmapItem
{Q_OBJECT
public:
    Grass(QGraphicsItem *parent=0);
    QPixmap GPixmap[3];
    Mytimer *grass_timer;
    void shake();
public slots:
    void setshake();
};

class Bulletin: public QGraphicsPixmapItem
{
public:
    Bulletin(TextInf bulletine_text,QGraphicsItem *parent=0);
    Bulletin(size_t n, TextInf* text, QGraphicsItem*parent=0);
    MyTextItem *textItem;
};
class Building:public QGraphicsPixmapItem{
public:
    Building(int k);
};
class Building1:public QGraphicsPixmapItem{
public:
    Building1(QGraphicsItem *parent=0);
};
class Building2:public QGraphicsPixmapItem{
public:
    Building2(QGraphicsItem *parent=0);
};

class Water:public QGraphicsPixmapItem{
public:
    Water(QGraphicsItem *parent=0);
};
class Path:public QGraphicsPixmapItem{
public:
    Path(QGraphicsItem *parent=0);
};
class UnvWall:public QGraphicsPixmapItem{
public:
    UnvWall(QGraphicsItem *parent=0);
    void change_pic(int n);
};
class ClickItem:public QObject,public QGraphicsPixmapItem{
Q_OBJECT
public:
    ClickItem(QGraphicsItem *parent=0);
    void change_item(int it);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void Itemclicked();
};
class Floor:public QGraphicsPixmapItem{
public:
    Floor(QGraphicsItem *parent=0);
    void change_bric(int m);
};
class Black:public QGraphicsPixmapItem{
public:
    Black(QGraphicsItem *parent=0);
};

#endif // BASE_H
