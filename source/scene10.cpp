#include"scene10.h"
#include"scene7.h"
#include"gates.h"
#include"gameenemy.h"
#include"mytimer.h"
#include"player.h"
#include"myview.h"
#include<QImage>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>
#include<QBrush>
#include<QTimer>

extern Scene7 *scene7;
extern Scene10 *scene10;

extern Myview* view;
Scene10::Scene10(int sx, int sy, QGraphicsScene *parent)
{
    qDebug()<< "scene10 created";
    setSceneRect(0,0,sx,sy);
    scene_timer=new Mytimer();
    MS_timer = new Mytimer();
    qDebug()<<"scene_timer in scene10 created";
    buildboundary(sx,sy);

    setBackgroundBrush(QBrush(QImage(":/images/images/gamebg.jpg")));
    for(size_t i=0,n=2;i<n;i++){
        buildwall(650,500+50*i);
        buildwall(100,50*i);
        buildwall(100,100+50*i);
    }
    for(size_t i=0,n=9;i<n;i++){
        buildwall(650,50*i);
    }
    for(size_t i=0,n=7;i<n;i++){
        buildwall(100,250+50*i);
    }

    QFont scene10_font("Scene10", 20, QFont::Helvetica);
    addText("Scene10",scene10_font);


}

void Scene10::addhero()
{
    scene_hero=new Player(scene10);
    addItem(scene_hero);
    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
    scene_hero->setFocus();
    qDebug()<<"hero added to scene10";


}

void Scene10::setconnection()
{
    connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
     connect(view,SIGNAL(signaltohero(bool,bool)),scene_hero,SLOT(setnext(bool,bool)));



     connect(scene_timer,SIGNAL(timeout()),scene_gate[0],SLOT(changescene()));
     connect(scene_gate[0],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[1],SLOT(changescene()));
     connect(scene_gate[1],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_gate[0],SIGNAL(signaltoscene_gateout(int)),scene7,SLOT(setheropos(int)));
     connect(scene_gate[1],SIGNAL(signaltoscene_gateout(int)),scene7,SLOT(setheropos(int)));


}

void Scene10::setheropos(int n)
{
    switch(n)
    {
      case 0:connect(MS_timer,SIGNAL(timeout()),scene10,SLOT(spawn()));
        scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());MS_timer->start(200);qDebug()<<"start";break;

      //case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
    }
    scene_hero->viewreset(scene_hero->x(),scene_hero->y());
}

void Scene10::spawn()
{
     GameEnemy* gameenemy= new GameEnemy();
     addItem(gameenemy);
     qDebug()<<"OK";
}

void Scene10::reset()
{
    scene_hero->setPos(700,550);
}
