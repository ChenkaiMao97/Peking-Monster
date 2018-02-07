#include"scene2.h"
#include"scene1.h"
#include"gates.h"
#include"mytimer.h"
#include"player.h"
#include"myview.h"

#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>

extern Scene1 *scene1;
extern Scene2 *scene2;
extern Myview* view;
Scene2::Scene2(int sx,int sy,QGraphicsScene *parent)
{

    qDebug()<<endl<<"scene2 created";
    setSceneRect(0,0,sx,sy);

    scene_timer=new Mytimer();
    qDebug()<<"scene_timer in scene2 created";

    //building*******************************
    buildboundary(sx,sy);
//    for(size_t i=0,n=5;i<n;i++)
//      { for(size_t j=0,n=3;j<n;j++)
//         buildgrass(50*i,550-50*j);}
for(size_t i=0,n=10;i<n;i++)
{buildgrass(500+50*i,700);}
for(size_t i=0,n=10;i<n;i++)
{buildwall(500+50*i,750);}
buildunvwall(500,650);

    //finish building************************

    QFont scene2_font("Scene2", 20, QFont::Helvetica);
    addText("Scene2",scene2_font);
    MS_timer = new Mytimer();
    scene_dialogue = new Dialogue(this);
    scene_dialogue->setFlag(QGraphicsItem::ItemIsFocusable);

}

void Scene2::setconnection()
{
    connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
    connect(view,SIGNAL(signaltohero(bool,bool)),scene_hero,SLOT(setnext(bool,bool)));

    connect(scene_timer,SIGNAL(timeout()),scene_gate[0],SLOT(changescene()));
    connect(scene_gate[0],SIGNAL(signaltoview(Mainscene*)),
        view,SLOT(set_scene(Mainscene *)));

    connect(scene_gate[0],SIGNAL(signaltoscene_gateout(int)),scene1,SLOT(setheropos(int)));

    connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),scene2,SLOT(faceItemEvent(QPointF)));
    connect(scene_dialogue,SIGNAL(Toscene_removehero()),scene2,SLOT(removeDialogue()));
}

void Scene2::addhero()
{
    scene_hero=new Player(scene2);
    addItem(scene_hero);


    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
    scene_hero->setFocus();

    qDebug()<<"hero added to scene2";
}

void Scene2::setheropos(int n)
{
    switch(n)
    {
      case 0: scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());break;
     case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
    }
    sound_changescene();
    scene_hero->viewreset(scene_hero->x(),scene_hero->y());
    view->set_bgm("qrc:/sounds/sounds/scene2_bgm.mp3");
}
void Scene2::faceItemEvent(QPointF point)
{ Mainscene::faceItemEvent(point);

}

void Scene2::removeDialogue()
{
 Mainscene::removeDialogue();
}

void Scene2::setAnimate_movePoints()
{
    Mainscene::setAnimate_movePoints();
}
