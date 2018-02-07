#include"mytimer.h"
#include"scene0.h"
#include"scene1.h"
#include"scene2.h"
#include"player.h"
#include"gates.h"
#include"myview.h"
#include"dialogue.h"

#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>
#include<QPushButton>
#include<QGraphicsTextItem>
#include<QTextDocument>

#define STEPSCALE 50

extern Scene1 *scene1;
extern Scene0 *scene0;
extern Scene2 *scene2;
extern Myview *view;

Scene0::Scene0(int sx, int sy, QGraphicsScene *parent)
{   qDebug()<<"scene0 created";
    setBgm("qrc:/sounds/sounds/bgm_1.mp3");
    qDebug()<<endl<<"scene0 created";
    setSceneRect(0,0,sx,sy);
    MS_timer = new Mytimer();
    scene_timer=new Mytimer();
    qDebug()<<"scene_timer in scene0 created";

    //building*******************************
    buildboundary(sx,sy);

    for(size_t i=0,n=5;i<n;i++)
      { for(size_t j=0,n=3;j<n;j++)
         buildgrass(STEPSCALE*i,11*STEPSCALE-STEPSCALE*j);}
    buildwall(3*STEPSCALE,4*STEPSCALE);
    TextInf str2[3]={{"I love Peking!",-2},{"I love Peking again!",-2},{"I love Peking FOREVER!",-2}};
    buildbulletin(4*STEPSCALE,1*STEPSCALE,TextInf("I love Peking!"));
    buildbulletin(4*STEPSCALE,2*STEPSCALE,3,str2);
    buildbulletin(4*STEPSCALE,3*STEPSCALE,TextInf("+1"));

//    QString BobString[4]={":/images/images/Bob2.jpeg",":/images/images/Bob3.jpeg",":/images/images/Bob4.jpeg",":/images/images/Bob5.jpeg"};
//    TextInf BobWords[4]={{"你好呀，我是Bob",0},{"北大真是个好地方呀",0},{"但是我要被退学了",0},{"看那边走过一只巨神",0}};
//    buildCharacter(2,BobString,200,200,4,BobWords,":/images/images/Bob_head.png",NULL,new characterData(_Bob_));

//    QString AliceString[4]={":/images/images/Bob2.jpeg",":/images/images/Bob3.jpeg",":/images/images/Bob4.jpeg",":/images/images/Bob5.jpeg"};
//    TextInf AliceWords[4]={{"Alice : 你好呀，我是Alice",0},{"我 ： 啊很高兴认识你，Alice！",-1},{"Alice ： 但是我要被退学了",0},{"我 ： 这里的人怎么都要被退学了呀orz。。",-1}};
//    buildCharacter(2,AliceString,500,500,4,AliceWords,":/images/images/Bob_head.png",NULL,NULL);

    //finish building************************
    QFont scene0_font("East Gate", 20, QFont::Helvetica);
    addText("East Gate",scene0_font);

    scene_dialogue = new Dialogue(this);
    scene_dialogue->setFlag(QGraphicsItem::ItemIsFocusable);

}

void Scene0::addhero()
{
    scene_hero=new Player(this);
    addItem(scene_hero);
    scene_hero->setPos(100,450);

    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
   // scene_hero->setAcceptedMouseButtons(0);
    scene_hero->setFocus();
    qDebug()<<"hero added to scene0";
}

void Scene0::setconnection()
{
    connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
    connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),scene0,SLOT(faceItemEvent(QPointF)));
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

    connect(scene_gate[0], SIGNAL(signaltoscene_gateout(int)), scene1, SLOT(setheropos(int)));
    connect(scene_gate[1], SIGNAL(signaltoscene_gateout(int)), scene1, SLOT(setheropos(int)));
    connect(scene_gate[2], SIGNAL(signaltoscene_gateout(int)), scene2, SLOT(setheropos(int)));

    connect(scene_dialogue,SIGNAL(Toscene_removehero()),scene0,SLOT(removeDialogue()));
}

void Scene0::setheropos(int n)
{
   switch(n)
   {
   case 0: scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());break;
   case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
   }

   view->set_bgm(getBgm());
   return;
}

void Scene0::faceItemEvent(QPointF point)
{
    Mainscene::faceItemEvent(point);
}

void Scene0::removeDialogue()
{
    removeItem(scene_dialogue);
    removeItem(scene_dialogue->Dialogue_TextItem);
    if(scene_NPC!=NULL)
    {removeItem(scene_head_Now);}
    scene_hero->setFocus();
}

void Scene0::setAnimate_movePoints()
{
    MS_timer->addtimes(MSA_times+1);
    if(MS_timer->gettimes()==0){MS_timer->stop(); MS_timer->disconnect(); return;}
    int movelengthx = MSA_xdistance/MSA_times;
    int movelengthy = MSA_ydistance/MSA_times;
    MSA_item->setPos(MSA_item->x()+movelengthx,MSA_item->y()+movelengthy);
}









