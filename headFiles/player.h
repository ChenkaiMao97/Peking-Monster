#ifndef PLAYER_H
#define PLAYER_H

#include"mainscene.h"
#include"monster.h"
#include"People.h"
#include"button.h"
#include"mytextitem.h"

#include<QGraphicsPixmapItem>
#include<QGraphicsItem>
#include<QKeyEvent>
#include<QObject>
#include"mytimer.h"
class Player:public QObject ,public QGraphicsPixmapItem
{Q_OBJECT
public:
  Player(){};
  Player(class Mainscene *scene_indefault,QGraphicsItem *parent=0);
  Mytimer* player_timer;

  void keyPressEvent(QKeyEvent *event);
  void judge();
  void viewreset(qreal x,qreal y);
  void move_annimate(char direction);
  class Mainscene* scene_playerin=NULL;
  void setface_toward(char ft);
  QPointF getFacePlace();

public slots:
   void setnext(bool bl_go,bool bl_shuaguai);
   void player_moveleft();
   void player_moveright();
   void player_moveup();
   void player_movedown();
signals:
   void itemsahead(QPointF);
   void Toscene_faceitem(QPointF);
   void Toview_checkBag();
private:
   bool can_go=0;
   bool monster_Canencounter=0;
   char face_toward=0;
};
class Character:public Player
{Q_OBJECT
public:
    Character(){}
    Character(int dir, QString* char_Pixmapdef, QString char_headdef1=NULL, QString char_headdef2=NULL,characterData* chaD=NULL);
    MyTextItem* char_Text;
    Button* char_button[2];
    characterData* char_charData;
    int char_dir;//2,3,4,5
    QPixmap char_Pixmap[4];
    QGraphicsPixmapItem *char_head[2]={NULL};
    Mytimer* char_timer;
    Mainscene* char_MS=NULL;
    void changeDir(int newdir);
    void setChar_Text(size_t n,TextInf* words);
    void move_annimate(char direction);
    void sleep(int msec);

public slots:
    void setanimate();
    void player_moveleft();
    void player_moveright();
    void player_moveup();
    void player_movedown();

};
#endif // PLAYER_H
