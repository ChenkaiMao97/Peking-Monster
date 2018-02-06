#ifndef SCENE2_H
#define SCENE2_H

#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene2 :public Mainscene
{Q_OBJECT

public:
Scene2(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();

public slots:
void setheropos(int n);
void faceItemEvent(QPointF point);
void removeDialogue();
void setAnimate_movePoints();
private:

};

#endif // SCENE2_H
