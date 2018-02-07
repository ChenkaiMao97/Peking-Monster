#ifndef SCENE1_H
#define SCENE1_H


#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene1 :public Mainscene
{Q_OBJECT

public:
Scene1(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();
void buildAnimate();
public slots:
 void setheropos(int n);
 void faceItemEvent(QPointF point);
 void removeDialogue();
 void setAnimate_movePoints();

private:

};

#endif // SCENE1_H
