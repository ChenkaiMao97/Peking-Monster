#ifndef SCENE3_H
#define SCENE3_H


#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene3 :public Mainscene
{Q_OBJECT

public:
Scene3(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();

public slots:
void setheropos(int n);
void faceItemEvent(QPointF point);
void removeDialogue();
void setAnimate_movePoints();
private:

};



#endif // SCENE3_H
