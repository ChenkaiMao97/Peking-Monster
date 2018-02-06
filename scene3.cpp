#include"scene3.h"
#include"scene1.h"
#include"gates.h"
#include"mytimer.h"
#include"player.h"
#include"myview.h"

#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>

extern Scene3 *scene3;
extern Scene1 *scene1;
extern Myview* view;
Scene3::Scene3(int sx, int sy, QGraphicsScene *parent)
{
    qDebug()<< "scene3 created";
    setSceneRect(0,0,sx,sy);
    scene_timer=new Mytimer();
    qDebug()<<"scene_timer in scene3 created";
    buildboundary(sx,sy);
    for(size_t i=0,n=5;i<n;i++)
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
    }

    QFont scene3_font("Scene3", 20, QFont::Helvetica);
    addText("Scene3",scene3_font);
    MS_timer = new Mytimer();
    scene_dialogue = new Dialogue(this);
    scene_dialogue->setFlag(QGraphicsItem::ItemIsFocusable);

}

void Scene3::addhero()
{
    scene_hero=new Player(scene3);
    addItem(scene_hero);
    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
    scene_hero->setFocus();
    qDebug()<<"hero added to scene3";


}

void Scene3::setconnection()
{
     connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
     connect(view,SIGNAL(signaltohero(bool,bool)),scene_hero,SLOT(setnext(bool,bool)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[0],SLOT(changescene()));
     connect(scene_gate[0],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_gate[0],SIGNAL(signaltoscene_gateout(int)),scene1,SLOT(setheropos(int)));

     connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),scene3,SLOT(faceItemEvent(QPointF)));
     connect(scene_dialogue,SIGNAL(Toscene_removehero()),scene3,SLOT(removeDialogue()));

}

void Scene3::setheropos(int n)
{
    switch(n)
    {
      case 0: scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());break;
      case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
    }
    scene_hero->viewreset(scene_hero->x(),scene_hero->y());
}
void Scene3::faceItemEvent(QPointF point)
{ Mainscene::faceItemEvent(point);

}

void Scene3::removeDialogue()
{
 Mainscene::removeDialogue();
}

void Scene3::setAnimate_movePoints()
{
    Mainscene::setAnimate_movePoints();
}
