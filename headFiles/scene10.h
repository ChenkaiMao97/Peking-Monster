#ifndef SCENE10_H
#define SCENE10_H

#include"mainscene.h"
#include"gates.h"
#include<QObject>
class Scene10 :public Mainscene
{Q_OBJECT

public:
Scene10(int sx,int sy,QGraphicsScene *parent=0);

virtual void addhero();
void setconnection();

public slots:
void setheropos(int n);
void spawn();
void reset();
private:

};

#endif // SCENE10_H
