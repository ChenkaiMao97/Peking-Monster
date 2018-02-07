#include"player.h"
#include"gates.h"
#include"myview.h"
#include<QDebug>
#include<QPixmap>
#include<QList>

#include<QGraphicsView>
#include<QGuiApplication>
#include<QTime>
#include<QTimer>

#define STEPSCALE 50
#define WALKTIME 40

extern Myview* view;
Player::Player(Mainscene *scene_indefault, QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{scene_playerin=scene_indefault;
 player_timer = new Mytimer();

 setPixmap(QPixmap(":/images/images/player_down1.png"));
 setScale(0.5);
 connect(this,SIGNAL(Toview_checkBag()),view,SLOT(setBagScene()));
 qDebug()<<"Hero pictured";

}

void Player::setnext(bool bl_go, bool bl_shuaguai)
{
    can_go=bl_go;
    monster_Canencounter=bl_shuaguai;
}



void Player::keyPressEvent(QKeyEvent *event)
{QPointF pt;
    if(event->key()==Qt::Key_Left)
    {setPixmap(QPixmap(":/images/images/player_left1.png"));
     setface_toward('l');
     pt=QPointF(x()-STEPSCALE+0.5*STEPSCALE,y()+0.5*STEPSCALE);
     emit itemsahead(pt);
        if(can_go)
        move_annimate('l');}

    else if(event->key()==Qt::Key_Right)
    {setPixmap(QPixmap(":/images/images/player_right1.png"));
     setface_toward('r');
     pt=QPointF(x()+STEPSCALE+0.5*STEPSCALE,y()+0.5*STEPSCALE) ;
     emit itemsahead(pt);
        if(can_go)
        move_annimate('r');}

    else if(event->key()==Qt::Key_Up)
    {setPixmap(QPixmap(":/images/images/player_up1.png"));
     setface_toward('u');
     pt = QPointF(x()+0.5*STEPSCALE,y()-STEPSCALE+0.5*STEPSCALE);
     emit itemsahead(pt);
        if(can_go)
        move_annimate('u');}

    else if(event->key()==Qt::Key_Down)
    {setPixmap(QPixmap(":/images/images/player_down1.png"));
     setface_toward('d');
     pt = QPointF(x()+0.5*STEPSCALE,y()+STEPSCALE+0.5*STEPSCALE);
     emit itemsahead(pt);
        if(can_go)
        move_annimate('d');}
    else if(event->key()==Qt::Key_Space)
    {   QPointF faceplace=getFacePlace();
        emit Toscene_faceitem(faceplace);
    }
    else if(event->key()==Qt::Key_B)
    {
        emit Toview_checkBag();
    }


}

void Player::judge()
{
    int random_number=rand()%20;
    if(random_number==0)
    {
        clearFocus();
        view->setsceneBackto(scene_playerin);
        view->setBgmBackTo(scene_playerin->getBgm());

        view->set_bgm("qrc:/sounds/sounds/battle1.mp3");
        QTimer::singleShot(2000,view,SLOT(setRandomBS()));

    }
    else return;
}



void Player::move_annimate(char direction)
{
    clearFocus();

    switch(direction)
    {
    case 'l':connect(player_timer,SIGNAL(timeout()),this,SLOT(player_moveleft())); break;
    case 'r':connect(player_timer,SIGNAL(timeout()),this,SLOT(player_moveright())); break;
    case 'u':connect(player_timer,SIGNAL(timeout()),this,SLOT(player_moveup())); break;
    case 'd':connect(player_timer,SIGNAL(timeout()),this,SLOT(player_movedown())); break;
    }
    player_timer->settimes(0);
    player_timer->setSingleShot(true);
    player_timer->start();
}

void Player::setface_toward(char ft)
{
    face_toward=ft;
}

QPointF Player::getFacePlace()
{QPointF point;
    switch(face_toward)
   {case 'l':point = QPointF(x()-STEPSCALE+0.5*STEPSCALE,y()+0.5*STEPSCALE);break;
    case 'r':point = QPointF(x()+STEPSCALE+0.5*STEPSCALE,y()+0.5*STEPSCALE);break;
    case 'u':point = QPointF(x()+0.5*STEPSCALE,y()-STEPSCALE+0.5*STEPSCALE);break;
    case 'd':point = QPointF(x()+0.5*STEPSCALE,y()+STEPSCALE+0.5*STEPSCALE);break;
   }
    return point;
}

 void Player::player_moveleft()
 {

        setPos(x()-STEPSCALE/5,y());
        switch(player_timer->gettimes())
        {case 0:setPixmap(QPixmap(":/images/images/player_left2.png"));break;
         case 1:setPixmap(QPixmap(":/images/images/player_left1.png"));break;
         case 2:setPixmap(QPixmap(":/images/images/player_left1.png"));break;
         case 3:setPixmap(QPixmap(":/images/images/player_left4.png"));break;
         case 4:setPixmap(QPixmap(":/images/images/player_left1.png"));break;
        }
       player_timer->addtimes(5);

       if(player_timer->gettimes()!=0){  player_timer->setSingleShot(true);
                                         player_timer->start(WALKTIME);
                                         viewreset(x(),y());
                                      }
       else {
             setFocus();
             scene_playerin->scene_timer->setSingleShot(true);
             scene_playerin->scene_timer->start(WALKTIME);
             viewreset(x(),y());
             disconnect(player_timer,SIGNAL(timeout()),this,SLOT(player_moveleft()));
             if(monster_Canencounter) {judge();} }

 }

 void Player::player_moveright()
 {

        setPos(x()+STEPSCALE/5,y());
        switch(player_timer->gettimes())
        {case 0:setPixmap(QPixmap(":/images/images/player_right2.png"));break;
         case 1:setPixmap(QPixmap(":/images/images/player_right1.png"));break;
         case 2:setPixmap(QPixmap(":/images/images/player_right1.png"));break;
         case 3:setPixmap(QPixmap(":/images/images/player_right4.png"));break;
         case 4:setPixmap(QPixmap(":/images/images/player_right1.png"));break;
        }
       player_timer->addtimes(5);

       if(player_timer->gettimes()!=0){  player_timer->setSingleShot(true);
                             player_timer->start(WALKTIME); viewreset(x(),y());}
       else {scene_playerin->scene_timer->setSingleShot(true);
             scene_playerin->scene_timer->start(WALKTIME);
             disconnect(player_timer,SIGNAL(timeout()),this,SLOT(player_moveright()));
             setFocus();
             viewreset(x(),y());
             if(monster_Canencounter) {judge();}}

 }

 void Player::player_moveup()
 {

        setPos(x(),y()-STEPSCALE/5);
        switch(player_timer->gettimes())
        {case 0:setPixmap(QPixmap(":/images/images/player_up2.png"));break;
         case 1:setPixmap(QPixmap(":/images/images/player_up1.png"));break;
         case 2:setPixmap(QPixmap(":/images/images/player_up1.png"));break;
         case 3:setPixmap(QPixmap(":/images/images/player_up4.png"));break;
         case 4:setPixmap(QPixmap(":/images/images/player_up1.png"));break;
        }
       player_timer->addtimes(5);

       if(player_timer->gettimes()!=0){  player_timer->setSingleShot(true);
                      player_timer->start(WALKTIME);viewreset(x(),y());}
       else {scene_playerin->scene_timer->setSingleShot(true);
             scene_playerin->scene_timer->start(WALKTIME);
             disconnect(player_timer,SIGNAL(timeout()),this,SLOT(player_moveup()));
             setFocus();
             viewreset(x(),y());
             if(monster_Canencounter) {judge();}}

 }
 void Player::player_movedown()
 {

        setPos(x(),y()+STEPSCALE/5);
        switch(player_timer->gettimes())
        {case 0:setPixmap(QPixmap(":/images/images/player_down2.png"));break;
         case 1:setPixmap(QPixmap(":/images/images/player_down1.png"));break;
         case 2:setPixmap(QPixmap(":/images/images/player_down1.png"));break;
         case 3:setPixmap(QPixmap(":/images/images/player_down4.png"));break;
         case 4:setPixmap(QPixmap(":/images/images/player_down1.png"));break;
        }
       player_timer->addtimes(5);

       if(player_timer->gettimes()!=0){  player_timer->setSingleShot(true);
                             player_timer->start(WALKTIME);viewreset(x(),y());}
       else {disconnect(player_timer,SIGNAL(timeout()),this,SLOT(player_movedown()));
             setFocus();
             scene_playerin->scene_timer->setSingleShot(true);
             scene_playerin->scene_timer->start(WALKTIME);
             viewreset(x(),y());
             if(monster_Canencounter) {judge();}}

 }

 void Player::viewreset(qreal x,qreal y)
 {int scenewidth=scene_playerin->width();
  int sceneheight=scene_playerin->height();

  int xstartpoint=0;
  int ystartpoint=0;

  if(x-8*STEPSCALE<0) xstartpoint=0;
  else if(x-8*STEPSCALE>=0&&x<scenewidth-8*STEPSCALE) xstartpoint=x-8*STEPSCALE;
  else if(x-8*STEPSCALE>=scenewidth-16*STEPSCALE) xstartpoint=scenewidth-16*STEPSCALE;

  if(y-6*STEPSCALE<0) ystartpoint=0;
  else if(y-6*STEPSCALE>=0&&y<sceneheight-6*STEPSCALE) ystartpoint=y-6*STEPSCALE;
  else if(y-6*STEPSCALE>=sceneheight-12*STEPSCALE) ystartpoint=sceneheight-12*STEPSCALE;

      view->setSceneRect(xstartpoint,ystartpoint,16*STEPSCALE,12*STEPSCALE);
 }

 Character::Character(int dir, QString *char_Pixmapdef, QString char_headdef1, QString char_headdef2, characterData *chaD)
 {
     char_timer = new Mytimer();
     player_timer=new Mytimer();
     if(chaD!=NULL){char_charData=new characterData(*chaD);}else{char_charData=NULL;}
     char_button[0]=new Button(100,40," ");
     char_button[1]=new Button(100,40," ");
     char_Text = new MyTextItem();
     char_dir = dir;
     char_Pixmap[0]=QPixmap(char_Pixmapdef[0]);
     char_Pixmap[1]=QPixmap(char_Pixmapdef[1]);
     char_Pixmap[2]=QPixmap(char_Pixmapdef[2]);
     char_Pixmap[3]=QPixmap(char_Pixmapdef[3]);
     if(char_dir==7){setPixmap(char_Pixmap[0]);}
     else if (char_dir==8){setPixmap(char_Pixmap[1]);}
     else{setPixmap(char_Pixmap[char_dir-2]);}
     if(char_headdef1!=NULL){char_head[0] = new QGraphicsPixmapItem(QPixmap(char_headdef1));}
     if(char_headdef2!=NULL){char_head[1] = new QGraphicsPixmapItem(QPixmap(char_headdef2));}

 }

 void Character::changeDir(int newdir)
 {
     if(char_dir==7){return;}
     else if (char_dir==8){return;}
     else {setPixmap(char_Pixmap[newdir-2]);return;}
 }

 void Character::setChar_Text(size_t n, TextInf *words)
 {
     for(size_t i=0;i<n;i++)
     {char_Text->addTextInf(words[i]);}
 }

 void Character::move_annimate(char direction)
 {
     switch(direction)
     {
     case 'l':connect(char_timer,SIGNAL(timeout()),this,SLOT(player_moveleft())); break;
     case 'r':connect(char_timer,SIGNAL(timeout()),this,SLOT(player_moveright())); break;
     case 'u':connect(char_timer,SIGNAL(timeout()),this,SLOT(player_moveup())); break;
     case 'd':connect(char_timer,SIGNAL(timeout()),this,SLOT(player_movedown())); break;
     }
     char_timer->settimes(0);
     char_timer->setSingleShot(true);
     char_timer->start(WALKTIME);
 }

 void Character::sleep(int msec)
 {
     QTime reachTime = QTime::currentTime().addMSecs(msec);
     while(QTime::currentTime()<reachTime)
     {QCoreApplication::processEvents(QEventLoop::AllEvents,100);}
     return;
 }

 void Character::setanimate()
 {qDebug()<<"animate";
   if(dynamic_cast<Mainscene*>(view->scene()))
   {
       Mainscene* MS = dynamic_cast<Mainscene*>(view->scene());
       if(MS->scene_hero==char_MS->scene_hero)
     {  qDebug()<<"scene right";
       char_dir=(char_dir+1)%4;
       switch (char_dir)
       {
          case 0: move_annimate('l');break;
          case 1: move_annimate('u');break;
          case 2: move_annimate('r');break;
          case 3: move_annimate('d');break;
       }

       QTimer::singleShot(5000,this,SLOT(setanimate()));
     }
     else{qDebug()<<"scene wrong";}
   }
   else{return;}
 }

 void Character::player_moveleft()
 {qDebug()<<"left";
     setPos(x()-3*STEPSCALE/5,y());
     setPixmap(char_Pixmap[3]);
     char_timer->addtimes(5);

    if(char_timer->gettimes()!=0){  char_timer->setSingleShot(true);
                                      char_timer->start(5*WALKTIME);
                                   }
    else {
          char_timer->setSingleShot(true);
          char_timer->start(5*WALKTIME);
          char_timer->disconnect();
          }
 }

 void Character::player_moveright()
 {qDebug()<<"right";
     setPos(x()+3*STEPSCALE/5,y());
     setPixmap(char_Pixmap[2]);
   char_timer->addtimes(5);

    if(char_timer->gettimes()!=0){  char_timer->setSingleShot(true);
                                      char_timer->start(5*WALKTIME);
                                   }
    else {
          char_timer->setSingleShot(true);
          char_timer->start(5*WALKTIME);
          char_timer->disconnect();
          }
 }

 void Character::player_moveup()
 {
     setPos(x(),y()-3*STEPSCALE/5);
     setPixmap(char_Pixmap[0]);
    char_timer->addtimes(5);

    if(char_timer->gettimes()!=0){  char_timer->setSingleShot(true);
                                      char_timer->start(5*WALKTIME);
                                   }
    else {
          char_timer->setSingleShot(true);
          char_timer->start(5*WALKTIME);
          char_timer->disconnect();
          }
 }

 void Character::player_movedown()
 {
     setPos(x(),y()+3*STEPSCALE/5);
     setPixmap(char_Pixmap[1]);
     char_timer->addtimes(5);

    if(char_timer->gettimes()!=0){  char_timer->setSingleShot(true);
                                      char_timer->start(5*WALKTIME);
                                   }
    else {
          char_timer->setSingleShot(true);
          char_timer->start(5*WALKTIME);
          char_timer->disconnect();
          }
 }
