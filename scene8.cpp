#include"scene8.h"
#include"scene7.h"
#include"gates.h"
#include"mytimer.h"
#include"player.h"
#include"myview.h"
#include"dialogue.h"

#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>

extern Scene7 *scene7;
extern Scene8 *scene8;
extern Myview* view;
Scene8::Scene8(int sx, int sy, QGraphicsScene *parent)
{
    qDebug()<< "scene8 created";
    setSceneRect(0,0,sx,sy);
    scene_timer=new Mytimer();
    qDebug()<<"scene_timer in scene8 created";
    buildboundary(sx,sy);
    for(size_t i=0,n=20;i<n;i++){
        for(size_t j=0,m=19;j<m;j++){
            buildblack(50*i,50*j);
        }
    }
    buildfloor(700,450,2);
    for(size_t i=0,n=2;i<n;i++){
        for(size_t j=0,m=4;j<m;j++){
            buildfloor(450+50*i,0+50*j,1);
            buildfloor(450+50*i,750+50*j,1);
            buildfloor(400+50*j,200+50*i,2);
            buildfloor(400+50*j,350+50*i,1);
            buildfloor(400+50*j,500+50*i,1);
            buildfloor(400+50*j,650+50*i,2);
        }
    }
    for(size_t i=0,n=2;i<n;i++){
        for(size_t j=0,m=2;j<m;j++){
            buildfloor(700+50*i,200+50*j,2);
            buildfloor(700+50*i,650+50*j,2);
        }
    }
    for(size_t i=0,n=2;i<n;i++){
        for(size_t j=0,m=11;j<m;j++){
            buildfloor(600+50*i,200+50*j,2);

        }
    }
    for(size_t i=0,n=13;i<n;i++){
        buildwall(350,150+50*i);
        buildwall(800,150+50*i);
    }
    for(size_t i=0,n=4;i<n;i++){
        buildwall(400,50*i);
        buildwall(400,750+50*i);
        buildwall(550,50*i);
        buildwall(550,750+50*i);
        buildwall(400+50*i,300);
        buildwall(400+50*i,450);
        buildwall(400+50*i,600);
        buildwall(600+50*i,150);
        buildwall(600+50*i,750);
    }
    for(size_t i=0,n=2;i<n;i++){
        for(size_t j=0,m=3;j<m;j++){
            buildwall(700+50*i,300+50*j);
            buildwall(700+50*i,500+50*j);

        }
    }

    builditem(750,200,5);
    builditem(750,250,5);
    builditem(750,650,6);
    builditem(750,700,6);
    builditem(400,350,4);
    builditem(400,500,4);
    builditem(500,0,4);
    builditem(450,900,4);
    builditem(450,0,1);
    builditem(400,400,2);
    builditem(400,550,2);
    builditem(500,900,3);

    QString AString[4]={":/images/images/A2.png",":/images/images/A3.png",":/images/images/A4.png",":/images/images/A5.png"};
        TextInf AWords[5]=
        {{"我：你好，请问...",-1},
         {"A：不要打扰我，没看见我正在赶DDL吗？！",0},
         {"我：我只是想问问...",-1},
         {"A：快走快走！要是做不完老师会杀了我的！",0},
         {"我：好吧，抱歉...",-1}};
        buildCharacter(4,AString,450,50,5,AWords,":/images/images/A_head.png",NULL,NULL);

        QString BString[4]={":/images/images/B2.png",":/images/images/B3.png",":/images/images/B4.png",":/images/images/B5.png"};
        TextInf BWords[4]=
        {{"我：你好...",-1},
         {"B：嘘，别说话！看...有没有感受到电磁学的力量！",0},
         {"我：什么力量-_-||？没感觉啊...",-1},
         {"B：当然是电磁学的力量！呵呵，看你这么无知，今天就让你好好见识一下吧！",0}};
        buildCharacter(5,BString,450,350,4,BWords,":/images/images/B_head.png",NULL,new characterData(_B_));

        QString CString[4]={":/images/images/C2.png",":/images/images/C3.png",":/images/images/C4.png",":/images/images/C5.png"};
        TextInf CWords[6]=
        {{"我：你好，请问你是学神吗？",-1},
         {"C：年轻人，你也是来挑战学神的吗？我劝你还是放弃吧。",0},
         {"我：啊？为什么？",-1},
         {"C:想当年，我打羽毛球时能用手感知风速，然后用空气动力学计算球的轨迹，打出完美一击，自以为天下无敌，于是来挑战学神。",0},
         {"C:最后...唉。所以我现在正在潜心修炼自己。你还是不要自不量力了，快走吧。",0},
         {"我：哦是这样啊，那你加油哦（憋装B了吧😒ヽ(･ω･´ﾒ)）",-1}};
        buildCharacter(5,CString,450,500,6,CWords,":/images/images/C_head.png",NULL,NULL);

        QString DString[4]={":/images/images/D2.png",":/images/images/D3.png",":/images/images/D4.png",":/images/images/D5.png"};
        TextInf DWords[3]=
        {{"D：你就是那个一直在找我的年轻人啊？",0},
         {"我：巨神！从小我就听说你GPA3.98的传奇了，钦慕已久，今日特来拜会！",-1},
         {"D：呵呵，我的GPA早就已经到4.0了。现在我是超神！既然你这么诚心诚意地来找我，那我就大发慈悲地让你开开眼界吧！",0}};
        buildCharacter(2,DString,450,700,3,DWords,":/images/images/D_head.png",NULL,new characterData(_D_));

    MS_timer = new Mytimer();
    scene_dialogue = new Dialogue(this);
    scene_dialogue->setFlag(QGraphicsItem::ItemIsFocusable);


}

void Scene8::addhero()
{
    scene_hero=new Player(scene8);
    addItem(scene_hero);
    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
    scene_hero->setFocus();
    qDebug()<<"hero added to scene8";


}

void Scene8::setconnection()
{
     connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
     connect(view,SIGNAL(signaltohero(bool,bool)),scene_hero,SLOT(setnext(bool,bool)));
     connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),this,SLOT(faceItemEvent(QPointF)));

     connect(scene_timer,SIGNAL(timeout()),scene_gate[0],SLOT(changescene()));
     connect(scene_gate[0],SIGNAL(signaltoview(Mainscene*)),
         view,SLOT(set_scene(Mainscene *)));

     connect(scene_gate[0],SIGNAL(signaltoscene_gateout(int)),scene7,SLOT(setheropos(int)));

     connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),scene8,SLOT(faceItemEvent(QPointF)));
     connect(scene_dialogue,SIGNAL(Toscene_removehero()),scene8,SLOT(removeDialogue()));

}

void Scene8::setheropos(int n)
{
    switch(n)
    {
      case 0: scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());break;
      //case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
    }
    scene_hero->viewreset(scene_hero->x(),scene_hero->y());
}

void Scene8::faceItemEvent(QPointF point)
{
    Mainscene::faceItemEvent(point);
}

void Scene8::removeDialogue()
{
    Mainscene::removeDialogue();
}

void Scene8::setAnimate_movePoints()
{
    Mainscene::setAnimate_movePoints();
}
