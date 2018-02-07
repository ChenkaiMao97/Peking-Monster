#ifndef SCENE0_H
#define SCENE0_H


#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene0 :public Mainscene
{Q_OBJECT

public:
Scene0(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();

public slots:
void setheropos(int n);
void faceItemEvent(QPointF point);
void removeDialogue();
void setAnimate_movePoints();

private:

};


#endif // SCENE0_H
