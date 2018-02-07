#ifndef GATES_H
#define GATES_H

#include<QGraphicsPolygonItem>
#include<QGraphicsPixmapItem>
#include"mainscene.h"
#include<QObject>

class Gate:public QObject, public QGraphicsPixmapItem
{Q_OBJECT
public:
    Gate(QGraphicsItem *parent=0);
void define_gatein(class Mainscene* scene_get);
void define_gateout(Mainscene* scene_get);
void define_gatenumber(int n);
void set_opacity();
public slots:
    void changescene();

signals:

    void signaltoview(class Mainscene* scene_show);
    void signaltoscene_gateout(int);

private:
    QGraphicsPolygonItem * gate_area;
    Mainscene *scene_gateout,*scene_gatein;
    int gate_number;

};

#endif // GATES_H
