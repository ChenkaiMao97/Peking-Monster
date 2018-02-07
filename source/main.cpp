#include<QApplication>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QDialog>
#include<QDebug>
#include<cstdlib>
#include<ctime>
#include"scene1.h"
#include"player.h"
#include"mainscene.h"
#include"scene0.h"
#include"myview.h"
#include"scene2.h"
#include "scene3.h"
//#include "scene4.h"
//#include"scene5.h"
#include"scene6.h"
#include"scene7.h"
#include"scene8.h"
#include"scene9.h"
#include"scene10.h"
Myview *view;
Scene1 *scene1;
Scene0 *scene0;
Scene2 *scene2;
Scene3 *scene3;
//Scene4 *scene4;
//Scene5 *scene5;
Scene6 *scene6;
Scene7 *scene7;
Scene8 *scene8;
Scene9 *scene9;
Scene10 *scene10;
int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);

    view= new Myview();

    scene1 = new Scene1(1350,1150);
    scene2 = new Scene2(1600,1200);
    scene3 = new Scene3(800,600);
    scene6 = new Scene6(800,600);
    scene7 = new Scene7(1300,600);
    scene8 = new Scene8(1000,950);
    scene9 = new Scene9(800,600);
    scene10= new Scene10(800,600);

    scene1->builddoors(scene1,scene2,1150,0,0);
    scene1->builddoors(scene1,scene3,1300,500,0);
    scene1->buildgates(scene1,scene6,950,1000,0);
    scene1->buildgates(scene1,scene7,1050,500,0);
    scene1->addhero();

    scene2->builddoors(scene2,scene1,400,0,0);
    scene2->addhero();

    scene3->builddoors(scene3,scene1,150,0,1);
    scene3->addhero();

    scene6->builddoors(scene6,scene1,150,0,2);
    scene6->addhero();

    scene7->builddoors(scene7,scene1,750,250,3);
    scene7->builddoors(scene7,scene8,550,250,0);
    scene7->buildgates(scene7,scene9,700,150,0);
    scene7->buildgates(scene7,scene10,650,150,0);
    scene7->addhero();

    scene8->builddoors(scene8,scene7,750,450,1);
    scene8->addhero();

    scene9->builddoors(scene9,scene7,400,550,2);
    scene9->addhero();

    scene10->builddoors(scene10,scene7,750,550,3);
    scene10->builddoors(scene10,scene7,0,550,4);
    scene10->addhero();

    scene1->setconnection();
    scene2->setconnection();
    scene3->setconnection();
    scene6->setconnection();
    scene7->setconnection();
    scene8->setconnection();
    scene9->setconnection();
    scene10->setconnection();


    view->setFixedSize(800,600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene1);
    scene1->scene_hero->viewreset(scene1->scene_hero->x(),scene1->scene_hero->y());
    view->set_bgm("qrc:/sounds/sounds/scene0_bgm.mp3");
    view->show();
    scene1->buildAnimate();
    //view->set_bgm("qrc:/sounds/sounds/scene0_bgm.mp3");
    return a.exec();
}




