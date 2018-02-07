#ifndef SCENE7_H
#define SCENE7_H

#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene7 :public Mainscene
{Q_OBJECT

public:
Scene7(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();

public slots:
void setheropos(int n);
void faceItemEvent(QPointF point);
void removeDialogue();
void setAnimate_movePoints();
private:

};


#endif // SCENE7_H
