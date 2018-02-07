#ifndef SCENE6_H
#define SCENE6_H
#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene6 :public Mainscene
{Q_OBJECT

public:
Scene6(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();

public slots:
void setheropos(int n);
void faceItemEvent(QPointF point);
void removeDialogue();
void setAnimate_movePoints();
private:

};

#endif // SCENE6_H
