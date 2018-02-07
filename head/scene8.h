#ifndef SCENE8_H
#define SCENE8_H

#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene8 :public Mainscene
{Q_OBJECT

public:
Scene8(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();

public slots:
void setheropos(int n);
 void faceItemEvent(QPointF point);
 void removeDialogue();
 void setAnimate_movePoints();
private:

};

#endif // SCENE8_H
