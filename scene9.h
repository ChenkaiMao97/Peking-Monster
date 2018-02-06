#ifndef SCENE9_H
#define SCENE9_H

#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene9 :public Mainscene
{Q_OBJECT

public:
Scene9(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();

public slots:
void setheropos(int n);
void faceItemEvent(QPointF point);
void removeDialogue();
void setAnimate_movePoints();
private:

};

#endif // SCENE9_H
