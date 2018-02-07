#include"base.h"
#include<QPixmap>
#include<cstdlib>
#include<QDebug>

Wall::Wall(QGraphicsItem *parent)
{
   setPixmap(QPixmap(":/images/images/wall1.png"));
   setScale(0.5);
}

Grass::Grass(QGraphicsItem *parent)
{
    grass_timer= new Mytimer();
    setPixmap(QPixmap(":/images/images/grass1.png"));
    GPixmap[0] = QPixmap(":/images/images/grass1.png");
    GPixmap[1] = QPixmap(":/images/images/grass2.png");
    GPixmap[2] = QPixmap(":/images/images/grass3.png");
    setScale(0.5);

}

void Grass::shake()
{
  grass_timer->settimes(0);
  grass_timer->setInterval(40);
  connect(grass_timer,SIGNAL(timeout()),this,SLOT(setshake()));
  grass_timer->start(40);
}

void Grass::setshake()
{
    grass_timer->addtimes(4);
    switch(grass_timer->gettimes())
    {
    case 0:setPixmap(GPixmap[0]);grass_timer->disconnect();break;
    case 1:setPixmap(GPixmap[1]);break;
    case 2:setPixmap(GPixmap[0]);break;
    case 3:setPixmap(GPixmap[2]);break;
    }
}

Bulletin::Bulletin(TextInf bulletine_text, QGraphicsItem *parent)
{
    textItem= new MyTextItem();
    textItem->addTextInf(bulletine_text);
    setPixmap(QPixmap(":/images/images/bulletin.png"));
    setScale(0.5);
}

Bulletin::Bulletin(size_t n, TextInf *text, QGraphicsItem *parent)
{
    textItem= new MyTextItem();
    for(size_t i=0;i<n;i++)
    {textItem->addTextInf(text[i]);}
    setPixmap(QPixmap(":/images/images/bulletin.png"));
    setScale(0.5);
}
Water::Water(QGraphicsItem *parent)
{    setPixmap(QPixmap(":/images/images/water.png"));
     setScale(0.5);
}
Path::Path(QGraphicsItem *parent)
{    setPixmap(QPixmap(":/images/images/_path1.png"));
     setScale(0.5);
}
Building::Building(int k)
{
    if(k=1){setPixmap(QPixmap(":/images/images/building1.png"));setScale(0.5);}
    if(k=2){setPixmap(QPixmap(":/images/images/building2.png"));setScale(0.5);}
    if(k=3){setPixmap(QPixmap(":/images/images/building3.png"));setScale(0.5);}
    if(k=4){setPixmap(QPixmap(":/images/images/building4.png"));setScale(0.5);}
}

UnvWall::UnvWall(QGraphicsItem *parent)
{
    int i = rand()%5+1;
    switch(i)
    {    case 1:setPixmap(QPixmap(":/images/images/_grassbg1.jpg"));break;
         case 2:setPixmap(QPixmap(":/images/images/_grassbg2.jpg"));break;
         case 3:setPixmap(QPixmap(":/images/images/_grassbg3.jpg"));break;
         case 4:setPixmap(QPixmap(":/images/images/_grassbg4.jpg"));break;
         case 5:setPixmap(QPixmap(":/images/images/_grassbg5.jpg"));break;    }
    setScale(0.5);
}

void UnvWall::change_pic(int n)
{
    switch(n)
    {    case 1:setPixmap(QPixmap(":/images/images/bed1.jpg"));break;
         case 2:setPixmap(QPixmap(":/images/images/bed2.png"));break;
         case 3:setPixmap(QPixmap(":/images/images/bed3.png"));break;
         case 4:setPixmap(QPixmap(":/images/images/bookshelf.png"));break;
         case 5:setPixmap(QPixmap(":/images/images/plant1.png"));break;
         case 6:setPixmap(QPixmap(":/images/images/plant2.png"));break;
         case 7:setPixmap(QPixmap(":/images/images/gamedoor.png"));break;
         case 8:setPixmap(QPixmap(":/images/images/shopdoor.png"));break;
         case 9:setPixmap(QPixmap(":/images/images/tree1.png"));break;
         case 10:setPixmap(QPixmap(":/images/images/tree2.png"));break;
         case 11:setPixmap(QPixmap(":/images/images/tree3.png"));break;
         case 12:setPixmap(QPixmap(":/images/images/tree4.png"));break;
    }
    setScale(0.5);
}
Building1::Building1(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/_building1.png"));
    setScale(0.5);
}
Building2::Building2(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/_building2.png"));
    setScale(0.5);
}
Floor::Floor(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/floor.jpg"));
    setScale(0.5);
}

void Floor::change_bric(int m)
{
    switch(m)
    {
    case 1:setPixmap(QPixmap(":/images/images/floor.jpg"));break;
    case 2:setPixmap(QPixmap(":/images/images/floor2.jpg"));break;
    }
    setScale(0.5);
}

Black::Black(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/black.png"));
    setScale(0.5);
}

ClickItem::ClickItem(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/black.png"));
    setScale(0.5);
}

void ClickItem::change_item(int it)
{
    switch(it){
    case 1:setPixmap(QPixmap(":/images/images/shopitem1.png"));break;
    case 2:setPixmap(QPixmap(":/images/images/shopitem2.png"));break;
    case 3:setPixmap(QPixmap(":/images/images/shopitem3.png"));break;
    }
    setScale(0.5);
}

void ClickItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit Itemclicked();
    qDebug()<<"item clicked";

}

