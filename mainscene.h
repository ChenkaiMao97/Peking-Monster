#ifndef MAINSCENE_H
#define MAINSCENE_H

#include<QGraphicsScene>
#include"gates.h"
#include"player.h"
#include"mytimer.h"
#include"base.h"
#include"dialogue.h"
#include<QVector>
class Mainscene :public QGraphicsScene
{

public:
    Mainscene();

    void buildwall(qreal wx,qreal wy);
    void buildgrass(qreal gx,qreal gy);
    void buildwater(qreal ax,qreal ay);
    void buildpath(qreal px, qreal py);
    void buildfloor(qreal fx, qreal fy,int bkd);
    void buildblack(qreal blx, qreal bly);
    void builditem(qreal ix, qreal iy,int kd);
    void buildclickitem(qreal cix, qreal ciy,int cit);
    void buildunvwall(qreal uwx, qreal uwy);
    void buildbuilding1(Mainscene* scene_at1, Mainscene* scene_bd1, qreal ux1, qreal uy1, int bdnum1);
    void buildbuilding2(Mainscene* scene_at2,Mainscene* scene_bd2,qreal ux2,qreal uy2,int bdnum2);

    void buildbulletin(qreal bx, qreal by, TextInf bulletin_Text);
    void buildbulletin(qreal bx, qreal by,int n,TextInf *text);
    void buildboundary(int bx,int by);
    void buildCharacter(int dir, QString *char_Pixmapdef,qreal cx, qreal cy,size_t n,TextInf *words, QString char_headdef1=NULL,QString char_headdef2=NULL, class characterData* chaD=NULL);
    void buildCharacterA(int dir, QString *char_Pixmapdef,qreal cx, qreal cy,size_t n,TextInf *words, QString char_headdef1=NULL,QString char_headdef2=NULL, class characterData* chaD=NULL,int i=0);
    void buildgates(Mainscene* scene_indefault,Mainscene* scene_outdefault,qreal gx,qreal gy,int num);
    void builddoors(Mainscene* scene_indefaultd,Mainscene* scene_outdefaultd,qreal dox,qreal doy,int donum);

    void animate_move(QGraphicsItem* item, int direction, int distance, int wholetime, int times);
    void animate_move(QGraphicsItem* item,QPointF pointaf, int wholetime, int times);
    void animate_move_head(QGraphicsPixmapItem* pItem,char dir );
    int judgeDirection(QPointF pN, QPointF pH);
    void sleep(int msec);

    void sound_changescene();

    void setBgm(QString defaultBgm);
    QString getBgm();

    virtual void setconnection()=0;
    virtual void addhero()=0;

    //public attributes
    QString bgm;
    class Character* scene_NPC=NULL;
    QVector<class Gate*>scene_gate;
    class Player *scene_hero;
    QGraphicsPixmapItem* scene_hero_head=NULL;
    QGraphicsPixmapItem* scene_head_Now=NULL;
    class Mytimer *scene_timer;
    class Dialogue *scene_dialogue;

    Mytimer* MS_timer;
    QGraphicsItem* MSA_item=NULL;
    int MSA_direction=1;
    int MSA_distance=0;
    int MSA_xdistance=0;
    int MSA_ydistance=0;
    int MSA_wholetime=0;
    int MSA_times=0;
public slots:
 void addDialogue();
 void faceItemEvent(QPointF point);
 void setAnimate_move();
 void removeDialogue();
 void setAnimate_movePoints();
signals:
 //void Toview_bgm(QString);
protected:

};
#endif // MAINSCENE_H
