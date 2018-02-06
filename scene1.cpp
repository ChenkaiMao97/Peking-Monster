#include"scene1.h"
#include"scene2.h"
#include"scene3.h"
#include"scene6.h"
#include"scene7.h"
#include"gates.h"
#include"mytimer.h"
#include"player.h"
#include"myview.h"

#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QDebug>

extern Scene1 *scene1;
extern Scene2 *scene2;
extern Scene3 *scene3;
extern Scene6 *scene6;
extern Scene7 *scene7;
extern Myview* view;
Scene1::Scene1(int sx, int sy, QGraphicsScene *parent)
{

    qDebug()<<endl<<"scene1 created";
    setSceneRect(0,0,sx,sy);//1350，1150

    scene_timer=new Mytimer();
    MS_timer = new Mytimer();
    qDebug()<<"scene_timer in scene1 created";

    //building*******************************
    buildboundary(sx,sy);
    for(size_t i=0,n=27;i<n;i++){
        for(size_t j=0,m=23;j<m;j++){
            buildunvwall(50*i,50*j);

        }
    }
    for(size_t i=0,n=24;i<n;i++){
        buildpath(50*i,800);
        buildpath(50*i,850);
        buildpath(50*i,1050);
        buildpath(50*i,1100);

    }
    for(size_t i=0,n=8;i<n;i++){
        for(size_t j=0,m=5;j<m;j++){
            buildpath(400+50*i,400+50*j);
        }
    }
    for(size_t i=0,n=13;i<n;i++){
        buildpath(300,150+50*i);
        buildpath(350,150+50*i);
        buildpath(800,150+50*i);
        buildpath(850,150+50*i);
        buildpath(1100,150+50*i);
        buildpath(1150,150+50*i);
    }
    buildpath(1150,50);
    buildpath(1150,100);
    buildpath(1200,500);
    buildpath(1250,500);
    for (size_t i=0,n=18;i<n;i++){
        buildpath(300+50*i,150);
        buildpath(300+50*i,200);
    }
    for(size_t i=0,n=3;i<n;i++){
        buildpath(0,900+50*i);
        buildpath(50,900+50*i);
        buildpath(500,900+50*i);
        buildpath(550,900+50*i);
        buildpath(600,900+50*i);
        buildpath(650,900+50*i);
        buildpath(1100,900+50*i);
        buildpath(1150,900+50*i);

    }
    buildbuilding2(scene1,scene1,100,250,4);
    buildbuilding1(scene1,scene1,400,250,2);
    buildbuilding1(scene1,scene1,400,650,2);
    buildbuilding1(scene1,scene1,100,900,2);
    buildbuilding2(scene1,scene1,900,250,3);
    buildbuilding1(scene1,scene1,700,900,1);


    for(size_t i=0,n=6;i<n;i++){
    builditem(1200,150+50*i,9);
    }
    for(size_t i=0,n=11;i<n;i++){
    builditem(1200,600+50*i,9);
    }
    for(size_t i=0,n=16;i<n;i++){
    builditem(300+50*i,100,12);
    }
    builditem(1200,450,10);
    builditem(1250,450,10);
    builditem(1300,450,10);
    builditem(1200,550,10);
    builditem(1250,550,10);
    builditem(1300,550,10);

    builditem(1200,0,10);
    builditem(1200,50,10);
    builditem(1200,100,10);
    builditem(1100,0,10);
    builditem(1100,50,10);
    builditem(1100,100,10);
    buildgrass(1100,900);
    for(size_t i=0,n=6;i<n;i++){
        for(size_t j=0,m=5;j<m;j++){
            buildgrass(450+50*i,400+50*j);
        }
    }
    QString JIAString[4]={":/images/images/JIA2.png",":/images/images/JIA3.png",":/images/images/JIA4.png",":/images/images/JIA5.png"};
        TextInf JIAWords[6]=
        {{"甲：同学你好！",0},
         {"我：啊，学长好...",-1},
         {"甲：不要叫学长，我这样GPA1.5的渣渣...唉，真羡慕那些巨神们...",0},
         {"我：巨神？",-1},
         {"甲：对啊，28楼有个超级学神，那可是GPA3.98的存在啊...同学你想不想去见识一下？",0},
         {"我：这么强...我当然要去膜拜一下啦，谢谢学长！",-1}};
        buildCharacter(3,JIAString,1100,1050,6,JIAWords,":/images/images/JIA_head.png",NULL,NULL);

        QString YIString[4]={":/images/images/YI2.png",":/images/images/YI3.png",":/images/images/YI4.png",":/images/images/YI5.png"};
        TextInf YIWords[2]=
        {{"乙：我要被ddl弄疯了...",0},
         {"乙：伟大的朗道之神请赐予我力量吧！",0}};
        buildCharacter(3,YIString,1100,400,2,YIWords,":/images/images/YI_head.png",NULL,NULL);

        QString BINGString[4]={":/images/images/BING2.png",":/images/images/BING3.png",":/images/images/BING4.png",":/images/images/BING5.png"};
        TextInf BINGWords[3]=
        {{"丙：这个“民主与科学”雕塑真是有趣...",0},
         {"丙：科学上面顶了个球...",0},
         {"丙：民主上面连个球都没有顶！😁",0}};
        buildCharacter(3,BINGString,750,450,3,BINGWords,":/images/images/BING_head.png",NULL,NULL);

        QString MString[4]={":/images/images/M2.png",":/images/images/M3.png",":/images/images/M4.png",":/images/images/M5.png"};
            TextInf MWords[4]=
            {{"情侣A：宝贝生日快乐~",0},
             {"情侣B：亲爱的你爱我吗？",1},
             {"情侣A: 当然爱你啦。",0},
             {"我：怎么到处都能看到情侣虐狗...秀分快！🌚🌚🌚",-1}};
            buildCharacter(7,MString,600,850,4,MWords,":/images/images/M_head.png",":/images/images/F_head.png",NULL);

            QString FString[4]={":/images/images/F2.png",":/images/images/F3.png",":/images/images/F4.png",":/images/images/F5.png"};
            TextInf FWords[4]=
            {{"情侣A：宝贝生日快乐~",0},
             {"情侣B：亲爱的你爱我吗？",1},
             {"情侣A: 当然爱你啦。",0},
             {"我：怎么到处都能看到情侣虐狗...秀分快！",-1}};
            buildCharacter(8,FString,600,800,4,FWords,":/images/images/M_head.png",":/images/images/F_head.png",NULL);

            TextInf str[5]=
                {{"欢迎来到北大妖怪！",-2},
                 {"在游戏中，你可以用键盘上下左右键控制人物行走，并且可以用空格键与NPC进行对话。",-2},
                 {"在场景中你有机会找到各类学神聚聚，并进入对战界面与之对战。",-2},
                 {"在对战界面中，你可以用高数、电磁学等等知识的力量为你的GPA而战。",-2},
                 {"祝你在北大妖怪中取得GPA4.0！",-2}};
                buildbulletin(1100,1000,5,str);
                buildbulletin(1100,550,TextInf("28楼"));
                buildbulletin(600,400,TextInf("29楼"));
                buildbulletin(300,1050,TextInf("30楼"));
                buildbulletin(300,550,TextInf("31楼"));
                buildbulletin(900,1050,TextInf("32楼"));
                buildbulletin(800,800,TextInf("35楼"));

    scene_dialogue = new Dialogue(this);
    scene_dialogue->setFlag(QGraphicsItem::ItemIsFocusable);
    //finish building************************
    QFont scene1_font("Dormitory", 20, QFont::Helvetica);
    addText("Dormitory",scene1_font);


}

void Scene1::setconnection()
{
    connect(scene_hero,SIGNAL(itemsahead(QPointF)),view,SLOT(item_at(QPointF)));
    connect(view,SIGNAL(signaltohero(bool,bool)),scene_hero,SLOT(setnext(bool,bool)));
    connect(scene_hero,SIGNAL(Toscene_faceitem(QPointF)),this,SLOT(faceItemEvent(QPointF)));

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

    connect(scene_gate[0],SIGNAL(signaltoscene_gateout(int)),scene2,SLOT(setheropos(int)));
    connect(scene_gate[1],SIGNAL(signaltoscene_gateout(int)),scene3,SLOT(setheropos(int)));
    connect(scene_gate[2],SIGNAL(signaltoscene_gateout(int)),scene6,SLOT(setheropos(int)));
    connect(scene_gate[3],SIGNAL(signaltoscene_gateout(int)),scene7,SLOT(setheropos(int)));

    connect(scene_dialogue,SIGNAL(Toscene_removehero()),scene1,SLOT(removeDialogue()));
}

void Scene1::buildAnimate()
{
    QString WString[4]={":/images/images/W2.png",":/images/images/W3.png",":/images/images/W4.png",":/images/images/W5.png"};
        TextInf WWords[2]=
        {{"W：我的GPA低得都要退学了...",0},
         {"W:我怀疑我长了假脑子。",0}};
        buildCharacterA(3,WString,550,550,2,WWords,":/images/images/W_head.png",NULL,NULL,1);

}

void Scene1::addhero()
{
    scene_hero=new Player(scene1);
    addItem(scene_hero);

    scene_hero->setPos(1150,1100);
    scene_hero->setFlag(QGraphicsItem::ItemIsFocusable);
    scene_hero->setFocus();

    qDebug()<<"hero added to scene1";
}

void Scene1::setheropos(int n)
{
    switch(n)
    {
      case 0: scene_hero->setPos(scene_gate[0]->x(),scene_gate[0]->y());break;
      case 1: scene_hero->setPos(scene_gate[1]->x(),scene_gate[1]->y());break;
      case 2: scene_hero->setPos(scene_gate[2]->x(),scene_gate[2]->y());break;
      case 3: scene_hero->setPos(scene_gate[3]->x(),scene_gate[3]->y());break;
    }
    sound_changescene();
    scene_hero->viewreset(scene_hero->x(),scene_hero->y());
    view->set_bgm("qrc:/sounds/sounds/scene1_bgm.mp3");
}

void Scene1::faceItemEvent(QPointF point)
{
    Mainscene::faceItemEvent(point);
}

void Scene1::removeDialogue()
{
 Mainscene::removeDialogue();
}

void Scene1::setAnimate_movePoints()
{
    Mainscene::setAnimate_movePoints();
}







