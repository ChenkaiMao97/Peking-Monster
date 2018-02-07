#include"scene9.h"
#include"scene7.h"
#include"gates.h"
#include"mytimer.h"
#include"player.h"
#include"myview.h"
#include<QImage>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>
#include<QBrush>

extern Scene7 *scene7;
extern Scene9 *scene9;
extern Myview* view;
Scene9::Scene9(int sx, int sy, QGraphicsScene *parent)
{
    qDebug()<< "scene9 created";
    setSceneRect(0,0,sx,sy);
    scene_timer=new Mytimer();
    qDebug()<<"scene_timer in scene9 created";
    buildboundary(sx,sy);
    setBackgroundBrush(QBrush(QImage(":/images/images/shopbg.jpg")));
    buildclickitem(50,50,1);



    QFont scene9_font("Scene9", 20, QFont::Helvetica);
    addText("Scene9",scene9_font);
    MS_timer = new Mytimer();
    scene_dialogue = new Dialogue(this);
    scene_dialogue->setFlag(QGraphicsItem::ItemIsFocusable);

}

void Scene9::addhero()
{
    scene_hero=new Player(scene9);
    addItem(scene_hero);
    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
    scene_hero->setFocus();
    qDebug()<<"hero added to scene9";


}

void Scene9::setconnection()
{
     connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
     connect(view,SIGNAL(signaltohero(bool,bool)),scene_hero,SLOT(setnext(bool,bool)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[0],SLOT(changescene()));
     connect(scene_gate[0],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_gate[0],SIGNAL(signaltoscene_gateout(int)),scene7,SLOT(setheropos(int)));

     connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),scene9,SLOT(faceItemEvent(QPointF)));
     connect(scene_dialogue,SIGNAL(Toscene_removehero()),scene9,SLOT(removeDialogue()));
}

void Scene9::setheropos(int n)
{
    switch(n)
    {
      case 0: scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());break;
      //case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
    }
    scene_hero->viewreset(scene_hero->x(),scene_hero->y());
}
void Scene9::faceItemEvent(QPointF point)
{ Mainscene::faceItemEvent(point);

}

void Scene9::removeDialogue()
{
 Mainscene::removeDialogue();
}

void Scene9::setAnimate_movePoints()
{
    Mainscene::setAnimate_movePoints();
}
