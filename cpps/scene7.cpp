#include"scene7.h"
#include"scene1.h"
#include"scene8.h"
#include"scene9.h"
#include"scene10.h"
#include"gates.h"
#include"mytimer.h"
#include"player.h"
#include"myview.h"

#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>

extern Scene7 *scene7;
extern Scene8 *scene8;
extern Scene1 *scene1;
extern Scene9 *scene9;
extern Scene10 *scene10;
extern Myview* view;
Scene7::Scene7(int sx, int sy, QGraphicsScene *parent)
{
    qDebug()<< "scene7 created";
    setSceneRect(0,0,sx,sy);
    scene_timer=new Mytimer();
    qDebug()<<"scene_timer in scene7 created";
    buildboundary(sx,sy);
    for(size_t i=0,n=26;i<n;i++){
        for(size_t j=0,m=12;j<m;j++){
            buildblack(50*i,50*j);
        }
    }
    buildfloor(600,150,2);
    for(size_t i=0,n=3;i<n;i++){
        for(size_t j=0,m=4;j<m;j++){
            buildfloor(600+50*i,200+50*j,2);
        }
    }
    for(size_t i=0,n=5;i<n;i++){
        buildwall(550+50*i,100);
        buildwall(550+50*i,400);
    }
    for(size_t i=0,n=2;i<n;i++){
        buildwall(550,150+50*i);
        buildwall(550,300+50*i);
        buildwall(750,150+50*i);
        buildwall(750,300+50*i);
    }

    builditem(650,150,7);
    builditem(700,150,8);

    QString LZString[4]={":/images/images/LZ2.png",":/images/images/LZ3.png",":/images/images/LZ4.png",":/images/images/LZ5.png"};
        TextInf LZWords[4]=
        {{"楼长：站住！哪个院的学生？来干什么的？",0},
         {"我：我是物理学院的，听说贵楼6层有几位隐逸不出的学神，特来拜会。",-1},
         {"楼长：[冷笑]呵呵，以前也有过几个不知天高地厚的学生来找过这些巨神，最后都被虐的连渣都不剩了。不知道你本事如何，上去吧。",0},
         {"我：我今天倒是要开开眼界。",-1}};
        buildCharacter(4,LZString,650,350,4,LZWords,":/images/images/LZ_head.png",NULL,NULL);

    QFont scene7_font("Scene7", 20, QFont::Helvetica);
    addText("Scene7",scene7_font);
    MS_timer = new Mytimer();
    scene_dialogue = new Dialogue(this);
    scene_dialogue->setFlag(QGraphicsItem::ItemIsFocusable);

}

void Scene7::addhero()
{
    scene_hero=new Player(scene7);
    addItem(scene_hero);
    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
    scene_hero->setFocus();
    qDebug()<<"hero added to scene7";


}

void Scene7::setconnection()
{
     connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
     connect(view,SIGNAL(signaltohero(bool,bool)),scene_hero,SLOT(setnext(bool,bool)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[0],SLOT(changescene()));
     connect(scene_gate[0],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[1],SLOT(changescene()));
     connect(scene_gate[1],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[2],SLOT(changescene()));
     connect(scene_gate[2],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[3],SLOT(changescene()));
     connect(scene_gate[3],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_gate[0],SIGNAL(signaltoscene_gateout(int)),scene1,SLOT(setheropos(int)));
     connect(scene_gate[1],SIGNAL(signaltoscene_gateout(int)),scene8,SLOT(setheropos(int)));
     connect(scene_gate[2],SIGNAL(signaltoscene_gateout(int)),scene9,SLOT(setheropos(int)));
     connect(scene_gate[3],SIGNAL(signaltoscene_gateout(int)),scene10,SLOT(setheropos(int)));

     connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),scene7,SLOT(faceItemEvent(QPointF)));
     connect(scene_dialogue,SIGNAL(Toscene_removehero()),scene7,SLOT(removeDialogue()));

}

void Scene7::setheropos(int n)
{
    scene10->MS_timer->stop();scene10->MS_timer->disconnect();
    switch(n)
    {
      case 0: scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());break;
      case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
      case 2: scene_hero->setPos(scene_gate[2]->x(),scene_gate[2]->y());break;
      case 3: scene_hero->setPos(scene_gate[3]->x(),scene_gate[3]->y());break;
      case 4: scene_hero->setPos(600,150);break;
    }
    scene_hero->viewreset(scene_hero->x(),scene_hero->y());
}
void Scene7::faceItemEvent(QPointF point)
{ Mainscene::faceItemEvent(point);

}

void Scene7::removeDialogue()
{
 Mainscene::removeDialogue();
}

void Scene7::setAnimate_movePoints()
{
    Mainscene::setAnimate_movePoints();
}
