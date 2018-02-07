#include"gates.h"
#include"scene1.h"
#include"scene0.h"
#include"mainscene.h"
#include"player.h"
#include"myview.h"
#include"mytimer.h"

#include<QGraphicsView>
#include<QGraphicsItem>
#include<QPixmap>
#include<QPointF>
#include<QPolygonF>
#include<QVector>
#include<QLineF>
#include<QList>
#include<QGraphicsScene>
#include<QTimer>
#include<QDebug>

extern Myview *view;
extern Mytimer* scene_timer;

Gate::Gate(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{   setPixmap(QPixmap(":images/images/gate.png"));
    setScale(0.5);

    QVector<QPointF> points;
    points<<QPointF(0,0)<<QPointF(1,0)<<QPointF(1,1)<<QPointF(0,1);

    int SCALE_FACTOR=100;
    for(size_t i=0, n=points.size();i<n;i++)
    {    points[i] *= SCALE_FACTOR;}

    QPolygonF polygon(points);
    gate_area=new QGraphicsPolygonItem(QPolygonF(points),this);

    QPointF poly_center(0.5,0.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene((poly_center));
    QPointF gate_center(x()+25,y()+25);
    QLineF ln(poly_center,gate_center);
    gate_area->setPos(x()+ln.dx(),y()+ln.dy());

}

void Gate::define_gatein(Mainscene *scene_get)
{
    scene_gatein=scene_get;
}

void Gate::define_gateout(Mainscene *scene_get)
{
    scene_gateout=scene_get;
}

void Gate::define_gatenumber(int n)
{
    gate_number=n;
}

void Gate::set_opacity()
{
    setOpacity(0.1);
}
void Gate::changescene()
{
 QList<QGraphicsItem *> colliding_items = collidingItems();
 for(size_t i=0,n=colliding_items.size();i<n;i++)
 {
     if(dynamic_cast<Player*>(colliding_items[i]))
      {
      emit signaltoscene_gateout(gate_number);
      emit signaltoview(scene_gateout);

      return;
      }
     else{continue;}
 }

return;
}




