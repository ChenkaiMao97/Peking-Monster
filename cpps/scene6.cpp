#include"scene6.h"
#include"scene1.h"
#include"gates.h"
#include"mytimer.h"
#include"player.h"
#include"myview.h"

#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>

extern Scene6 *scene6;
extern Scene1 *scene1;
extern Myview* view;
Scene6::Scene6(int sx, int sy, QGraphicsScene *parent)
{
    qDebug()<< "scene6 created";
    setSceneRect(0,0,sx,sy);
    scene_timer=new Mytimer();
    qDebug()<<"scene_timer in scene6 created";
    buildboundary(sx,sy);
    /*for(size_t i=0,n=5;i<n;i++)
    {buildgrass(350,200+50*i);
     buildgrass(300,200+50*i);
     buildgrass(250,200+50*i);
    }
    for(size_t i=0,n=5;i<n;i++)
    {buildwall(400,200+50*i);
     buildwall(450,200+50*i);
    }
    buildwater(500,200);
    //buildbuilding(250,200);
    for(size_t i=0,n=5;i<n;i++)
    {buildpath(150,200+50*i);
    }*/

    QFont scene6_font("Scene6", 20, QFont::Helvetica);
    addText("Scene6",scene6_font);
    MS_timer = new Mytimer();
    scene_dialogue = new Dialogue(this);
    scene_dialogue->setFlag(QGraphicsItem::ItemIsFocusable);

}

void Scene6::addhero()
{
    scene_hero=new Player(scene6);
    addItem(scene_hero);
    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
    scene_hero->setFocus();
    qDebug()<<"hero added to scene6";


}

void Scene6::setconnection()
{
     connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
     connect(view,SIGNAL(signaltohero(bool,bool)),scene_hero,SLOT(setnext(bool,bool)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[0],SLOT(changescene()));
     connect(scene_gate[0],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_gate[0],SIGNAL(signaltoscene_gateout(int)),scene1,SLOT(setheropos(int)));

     connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),scene6,SLOT(faceItemEvent(QPointF)));
     connect(scene_dialogue,SIGNAL(Toscene_removehero()),scene6,SLOT(removeDialogue()));

}

void Scene6::setheropos(int n)
{
    switch(n)
    {
      case 0: scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());break;
      //case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
    }
    scene_hero->viewreset(scene_hero->x(),scene_hero->y());
}
void Scene6::faceItemEvent(QPointF point)
{ Mainscene::faceItemEvent(point);

}

void Scene6::removeDialogue()
{
 Mainscene::removeDialogue();
}

void Scene6::setAnimate_movePoints()
{
    Mainscene::setAnimate_movePoints();
}
