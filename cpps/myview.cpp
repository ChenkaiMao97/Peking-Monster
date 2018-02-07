#include"myview.h"
#include"mainscene.h"
#include"base.h"
#include"gates.h"
#include"battlescene.h"
#include"PKUmon.h"
#include<QTransform>
#include<QDebug>
#include<QString>
#include<QMediaPlaylist>

#define INITIALX 205
#define INITIALY 65
#define STEP 78

Myview::Myview(QGraphicsView *parent)
{
   view_BS=NULL;
   playlist = new QMediaPlaylist();
   view_bgm = new QMediaPlayer();

   mon m1 = mon(Math_GDSX_3), m2 = mon(Math_XXDS_2), m3 = mon(PHYSICS_LX_1);
   m1.setLevel(7); m2.setLevel(7); m3.setLevel(7);
   backpack bag(m1,m2,m3);
   view_hero = new playerData("hero",bag);qDebug()<<view_hero->Mon(1)->blood();
   view_hero_PixMap = new QGraphicsPixmapItem(QPixmap(":/images/images/view_hero_Pixmap.png"));
   view_hero_PixMap->setScale(0.75);
   for(size_t i=1,n=view_hero->size();i<=n;i++)
   {view_hero->Mon(i)->mon_MonsterIcon->Icon_Monster->setM_owned(true);}
}

void Myview::setSceneAndBGM()
{
 if(dynamic_cast<Mainscene*>(scene()))
 {
  setsceneBackto(dynamic_cast<Mainscene*>(scene()));
  setBgmBackTo(dynamic_cast<Mainscene*>(scene())->getBgm());
 }
 else{return;}
}

void Myview::setsceneBackto(Mainscene *scene)
{
    if(scene==NULL){return;}
    scene_BackTo=scene;
    set_bgm(bgm_BackTo);
}

void Myview::setBgmBackTo(QString bgmB)
{
    bgm_BackTo=bgmB;
}

void Myview::setBattleScene(studentData& stu)
{
    setSceneRect(0,0,800,600);
    view_BS = new BattleScene(stu);
    setScene(view_BS);
    view_BS->setStage_ButtonOnly(true);
}

void Myview::setBattleScene(characterData& character)
{
    setSceneRect(0,0,800,600);
    view_BS = new BattleScene(character);
    setScene(view_BS);
    view_BS->setStage_ButtonOnly(true);
}

void Myview::setRandomBS()
{   qDebug()<<"random set";
    studentData s=opponent(*view_hero);
    setBattleScene(s);
}

void Myview::setInitial()
{
    qDebug()<<"state_setInitial";
    for(size_t i=0,n=view_hero->size();i<n;i++)
    {dynamic_cast<BattleScene*>(scene())->BS_monIC_PL[i]->changeColorMode();}
    dynamic_cast<Square*>(itemAt(INITIALX,INITIALY))->changeColorMode();
    dynamic_cast<BattleScene*>(scene())->setShining_Place(dynamic_cast<Square*>(itemAt(INITIALX,INITIALY)));   
    dynamic_cast<BattleScene*>(scene())->setStage_ButtonOnly(false);
    dynamic_cast<BattleScene*>(scene())->setStage_Initial(true);

    return;
}

void Myview::setMainscene()
{

    setScene(scene_BackTo);
    set_bgm(bgm_BackTo);
    scene_BackTo->scene_hero->viewreset(scene_BackTo->scene_hero->x(),scene_BackTo->scene_hero->y());
    scene_BackTo->scene_hero->setFocus();

}

void Myview::setBagScene()
{
    int INIx=50,INIy=200,Step=150,height=75;
    BattleScene* BagScene = new BattleScene();
    BagScene->setStage_ButtonOnly(true);
    for(size_t i=0,n=view_hero->size();i<n;i++)
    {
        mon m=*view_hero->Mon(i+1);
        BagScene->BS_monIB_PL[i] = transMon(m);
        BagScene->BS_monIC_PL[i] = BagScene->BS_monIB_PL[i].mon_MonsterIcon;
        BagScene->BS_monIC_PL[i]->setIconColor();
        BagScene->BS_monIC_PL[i]->Icon_Tag = new Tag(&BagScene->BS_monIB_PL[i]);

    }
    BagScene->setSceneRect(0,0,800,600);
    BagScene->setBackgroundBrush(QBrush(QImage(":/images/images/Bag_bg.jpg")));
    BagScene->addItem(view_hero_PixMap);view_hero_PixMap->setPos(550,90);
    setsceneBackto(dynamic_cast<Mainscene*>(scene()));
    Button* Back = new Button(100,40,"Back",NULL);
    connect(Back,SIGNAL(clicked()),this,SLOT(setMainscene()));
    BagScene->addItem(Back);Back->setPos(640,540);
    for(size_t i=0,n=view_hero->size();i<n;i++)
    {
        QBrush brush;
        brush.setStyle(Qt::Dense3Pattern);
        brush.setColor(Qt::gray);
        BagScene->addEllipse(INIx+i*Step,INIy/*+i*Step+height*/,100,30,QPen(),brush);
        //view_hero->Mon(i+1)->mon_MonsterIcon->setScale(1.3);
        BagScene->addItem(view_hero->Mon(i+1)->mon_MonsterIcon);
        view_hero->Mon(i+1)->mon_MonsterIcon->setPos(INIx+i*Step+13,INIy-50/*+i*Step-25*/);
    }
    for(size_t i=view_hero->size();i<6;i++)
    {
        QBrush brush;
        brush.setStyle(Qt::Dense3Pattern);
        brush.setColor(Qt::gray);
        BagScene->addEllipse(INIx+(i-3)*Step,INIy+200/*+i*Step+height*/,100,30,QPen(),brush);
    }
    setScene(BagScene);
    setSceneRect(0,0,800,600);

}

void Myview::set_scene(Mainscene *scene_show)
{
    setScene(scene_show);
}

void Myview::item_at(QPointF point)
{
    bool cango,shuaguai;

        if(dynamic_cast<ClickItem*>(scene()->itemAt(point,QTransform()))||dynamic_cast<Black*>(scene()->itemAt(point,QTransform()))||
                dynamic_cast<Wall*>(scene()->itemAt(point,QTransform()))||dynamic_cast<Bulletin*>(scene()->itemAt(point,QTransform()))||
                dynamic_cast<Water*>(scene()->itemAt(point,QTransform()))||dynamic_cast<Building*>(scene()->itemAt(point,QTransform()))||
                dynamic_cast<UnvWall*>(scene()->itemAt(point,QTransform()))||dynamic_cast<Building1*>(scene()->itemAt(point,QTransform()))||
                dynamic_cast<Building2*>(scene()->itemAt(point,QTransform())))//itemAt is according to the view!!
        {cango=false;qDebug()<<"you can not go";}
        else if (dynamic_cast<Character*>(scene()->itemAt(point,QTransform())))
            {cango=false;qDebug()<<"you can not go";}
        else {cango=true;}


        if(dynamic_cast<Grass*>(scene()->itemAt(point,QTransform())))
        {
        dynamic_cast<Grass*>(scene()->itemAt(point,QTransform()))->shake();
            shuaguai=true;
        }
        else {shuaguai=false;}

        emit signaltohero(cango,shuaguai);

}

void Myview::set_bgm(QString url)
{
    playlist->clear();
    playlist->addMedia(QUrl(url));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    view_bgm->setPlaylist(playlist);
    view_bgm->play();

}

