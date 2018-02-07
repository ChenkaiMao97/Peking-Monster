#include<QGraphicsItem>
#include"mainscene.h"
#include"player.h"
#include"myview.h"
#include<QGraphicsScene>
#include"gates.h"
#include"scene1.h"
#include<QDebug>
#include<QMediaPlayer>
#include<QTime>
#include<QCoreApplication>
#define MAPSCALE 50
#define STEPSCALE 50
#define WALKTIME 40
extern Myview* view;
extern Scene1* scene1;
Mainscene::Mainscene()
{
scene_hero_head=new QGraphicsPixmapItem(QPixmap(":/images/images/hero_head.png"));
scene_NPC=new Character();
}

void Mainscene::buildwall(qreal wx, qreal wy)
{
    Wall *wall=new Wall();
    addItem(wall);
    wall->setPos(wx,wy);

}

void Mainscene::buildgrass(qreal gx, qreal gy)
{
    Grass *grass=new Grass();
    addItem(grass);
    grass->setPos(gx,gy);
}

void Mainscene::buildwater(qreal ax, qreal ay)
{
    Water *water=new Water();
    addItem(water);
    water->setPos(ax,ay);
}
void Mainscene::buildpath(qreal px, qreal py)
{
    Path *path=new Path();
    addItem(path);
    path->setPos(px,py);
}

void Mainscene::buildfloor(qreal fx, qreal fy, int bkd)
{
    Floor *floor=new Floor();
    floor->change_bric(bkd);
    addItem(floor);
    floor->setPos(fx,fy);
}

void Mainscene::buildblack(qreal blx, qreal bly)
{
    Black *black=new Black();
    addItem(black);
    black->setPos(blx,bly);
    black->setZValue(-2);
}

void Mainscene::builditem(qreal ix, qreal iy, int kd)
{
    UnvWall * unvwall=new UnvWall();
    unvwall->change_pic(kd);
    addItem(unvwall);
    unvwall->setPos(ix,iy);
}

void Mainscene::buildclickitem(qreal cix, qreal ciy, int cit)
{
    ClickItem * clickitem=new ClickItem();
    clickitem->change_item(cit);
    addItem(clickitem);
    clickitem->setPos(cix,ciy);
}

void Mainscene::buildunvwall(qreal uwx, qreal uwy)
{
    UnvWall * unvwall=new UnvWall();
    addItem(unvwall);
    unvwall->setPos(uwx,uwy);
    unvwall->setZValue(-2);

}


void Mainscene::buildbuilding1(Mainscene *scene_at1, Mainscene *scene_bd1, qreal ux1, qreal uy1, int bdnum1)
{

    Building1 *building1=new Building1();
    addItem(building1);
    building1->setPos(ux1,uy1);
    building1->setZValue(-1);


}

void Mainscene::buildbuilding2(Mainscene *scene_at2, Mainscene *scene_bd2, qreal ux2, qreal uy2, int bdnum2)
{
    Building2 *building2=new Building2();
    addItem(building2);
    building2->setPos(ux2,uy2);
    building2->setZValue(-1);
}

void Mainscene::buildbulletin(qreal bx, qreal by, TextInf bulletin_Text)
{
    Bulletin *bulletin = new Bulletin(bulletin_Text);
    addItem(bulletin);
    bulletin->setPos(bx,by);
}

void Mainscene::buildbulletin(qreal bx, qreal by, int n, TextInf *text)
{
    Bulletin *bulletin = new Bulletin(n,text);
    addItem(bulletin);
    bulletin->setPos(bx,by);
}


void Mainscene::sound_changescene()
{
QMediaPlayer *sounds_changescene = new QMediaPlayer();
sounds_changescene->setMedia(QUrl("qrc:/sounds/sounds/changescene.wav"));
sounds_changescene->play();
qDebug()<<"sounds played";
}

void Mainscene::addDialogue()
{
    addItem(scene_dialogue);  
    scene_dialogue->setPos(view->sceneRect().x()+10,view->sceneRect().y()+490);
    scene_dialogue->Dialogue_TextItem->setNextToSay();
    addItem(scene_dialogue->Dialogue_TextItem);
    scene_dialogue->Dialogue_TextItem->setPos(view->sceneRect().x()+30,view->sceneRect().y()+510);
    scene_dialogue->Dialogue_TextItem->setTextWidth(740);
    scene_hero->clearFocus();

    scene_dialogue->setFocus();

}

void Mainscene::removeDialogue()
{
    removeItem(scene_dialogue);
    removeItem(scene_dialogue->Dialogue_TextItem);
    if(scene_NPC!=NULL)
    {scene_NPC->changeDir(scene_NPC->char_dir);removeItem(scene_head_Now);}
    scene_hero->setFocus();
    scene_head_Now=NULL;
    scene_NPC=NULL;
}

void Mainscene::faceItemEvent(QPointF point)
{qDebug()<<"faceItemEvent";
    if(dynamic_cast<Bulletin*>(itemAt(point,QTransform())))
           {
            scene_dialogue->setTextItem(dynamic_cast<Bulletin*>(itemAt(point,QTransform()))->textItem);          
            addDialogue();
            }
        else if(dynamic_cast<Character*>(itemAt(point,QTransform())))
           {qDebug()<<"character";           
            scene_dialogue->setTextItem(dynamic_cast<Character*>(itemAt(point,QTransform()))->char_Text);
            //scene_dialogue->head_NPC=dynamic_cast<Character*>(itemAt(point,QTransform()))->char_head[0];
            scene_NPC=dynamic_cast<Character*>(itemAt(point,QTransform()));
            scene_dialogue->dialogue_char=scene_NPC;
            scene_head_Now = scene_NPC->char_head[0];
            qDebug()<<scene_NPC->char_dir;
            addItem(scene_head_Now);scene_head_Now->setZValue(1);
            scene_head_Now->setPos(view->sceneRect().x()+900,view->sceneRect().y()+300);
            animate_move(scene_head_Now,QPoint(view->sceneRect().x()+580,view->sceneRect().y()+300),200,20);
            addDialogue();
            int a = judgeDirection(point,scene_hero->pos());
            scene_NPC->changeDir(a);
           }
        else{return;}
}

void Mainscene::setAnimate_movePoints()
{
    MS_timer->addtimes(MSA_times+1);
    if(MS_timer->gettimes()==0){MS_timer->stop(); MS_timer->disconnect(); return;}
    int movelengthx = MSA_xdistance/MSA_times;
    int movelengthy = MSA_ydistance/MSA_times;
    MSA_item->setPos(MSA_item->x()+movelengthx,MSA_item->y()+movelengthy);
}

void Mainscene::buildboundary(int bx, int by)
{for(size_t i=0,n=bx/MAPSCALE;i<n;i++)
            buildwall(MAPSCALE*i,-MAPSCALE);
 for(size_t i=0,n=bx/MAPSCALE;i<n;i++)
            buildwall(MAPSCALE*i,by);
 for(size_t i=0,n=by/MAPSCALE;i<n;i++)
            buildwall(bx,i*MAPSCALE);
 for(size_t i=0,n=by/MAPSCALE;i<n;i++)
            buildwall(-MAPSCALE,i*MAPSCALE);


}

void Mainscene::buildCharacter(int dir, QString *char_Pixmapdef, qreal cx, qreal cy,size_t n,TextInf *words, QString char_headdef1,QString char_headdef2,characterData* chaD)
{
    Character* newChar = new Character(dir,char_Pixmapdef,char_headdef1,char_headdef2,chaD);
    newChar->setChar_Text(n,words);
    addItem(newChar);
    newChar->changeDir(newChar->char_dir);
    newChar->setPos(cx,cy);
}

void Mainscene::buildCharacterA(int dir, QString *char_Pixmapdef, qreal cx, qreal cy, size_t n, TextInf *words, QString char_headdef1, QString char_headdef2, characterData *chaD, int i)
{
    Character* newChar = new Character(dir,char_Pixmapdef,char_headdef1,char_headdef2,chaD);
    newChar->setChar_Text(n,words);
    addItem(newChar);
    newChar->changeDir(newChar->char_dir);
    newChar->setPos(cx,cy);
    switch (i) {
    case 1:newChar->char_MS = scene1; newChar->setanimate();break;
    default: break;
    }
}

void Mainscene::buildgates(Mainscene *scene_indefault, Mainscene *scene_outdefault, qreal gx, qreal gy, int num)
{   scene_gate.append(new Gate());

    int n= scene_gate.size();
    addItem(scene_gate[n-1]);
    scene_gate[n-1]->setPos(gx,gy);
    scene_gate[n-1]->set_opacity();

    scene_gate[n-1]->define_gatein(scene_indefault);
    scene_gate[n-1]->define_gateout(scene_outdefault);
    scene_gate[n-1]->define_gatenumber(num);
}

void Mainscene::builddoors(Mainscene *scene_indefaultd, Mainscene *scene_outdefaultd, qreal dox, qreal doy, int donum)
{
    scene_gate.append(new Gate());

        int n= scene_gate.size();
        addItem(scene_gate[n-1]);
        scene_gate[n-1]->setPos(dox,doy);


        scene_gate[n-1]->define_gatein(scene_indefaultd);
        scene_gate[n-1]->define_gateout(scene_outdefaultd);
        scene_gate[n-1]->define_gatenumber(donum);
}

void Mainscene::animate_move(QGraphicsItem *item, int direction, int distance, int wholetime, int times)
{
    MSA_item=item;MSA_distance=distance;MSA_wholetime=wholetime;MSA_times=times;
    MSA_direction=direction;
    if(MSA_direction==1){return;}
    MS_timer->settimes(0);
    MS_timer->setInterval(wholetime/times);
    MS_timer->start();
    connect(MS_timer,SIGNAL(timeout()),this,SLOT(setAnimate_move()));
}

void Mainscene::animate_move(QGraphicsItem *item, QPointF pointaf, int wholetime, int times)
{
    MSA_item=item;MSA_xdistance=pointaf.x()-item->x();MSA_ydistance=pointaf.y()-item->y();
    MSA_wholetime=wholetime;MSA_times=times;
    MS_timer->settimes(0);
    MS_timer->setInterval(wholetime/times);
    MS_timer->start();
    connect(MS_timer,SIGNAL(timeout()),this,SLOT(setAnimate_movePoints()));

}

void Mainscene::animate_move_head(QGraphicsPixmapItem *pItem, char dir)
{
    if(dir=='l')
    {
        addItem(pItem);pItem->setPos(-200,300);
        animate_move(pItem,QPointF(20,300),200,20);
    }
    if(dir=='r')
    {
        addItem(pItem);pItem->setPos(800,300);
        animate_move(pItem,QPointF(600,300),200,20);
    }
}

int Mainscene::judgeDirection(QPointF pN, QPointF pH)
{
    int xN=pN.x(),xH=pH.x()+STEPSCALE/2,yN=pN.y(),yH=pH.y()+STEPSCALE/2;
    if(xN==xH)
    {
        if(yH-yN==STEPSCALE){return 3;}
        if(yH-yN==-STEPSCALE){return 2;}
    }
    else if(xH-xN==STEPSCALE){return 4;}
    else if(xH-xN==-STEPSCALE){return 5;}

}

void Mainscene::sleep(int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {QCoreApplication::processEvents(QEventLoop::AllEvents,100);}
    return;
}

void Mainscene::setAnimate_move()
{
    MS_timer->addtimes(MSA_times+1);
    if(MS_timer->gettimes()==0){MS_timer->stop(); MS_timer->disconnect(); return;}
    int movelength = MSA_distance/MSA_times;
    switch(MSA_direction)
    {
    case '5':MSA_item->setPos(MSA_item->x()-movelength,MSA_item->y());break;
    case '4':MSA_item->setPos(MSA_item->x()+movelength,MSA_item->y());break;
    case '2':MSA_item->setPos(MSA_item->x(),MSA_item->y()-movelength);break;
    case '3':MSA_item->setPos(MSA_item->x(),MSA_item->y()+movelength);break;
    }
}

void Mainscene::setBgm(QString defaultBgm)
{
    bgm=defaultBgm;
}

QString Mainscene::getBgm()
{
    return bgm;
}
