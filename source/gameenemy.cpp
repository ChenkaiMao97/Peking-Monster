#include "gameenemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "scene10.h"
#include"player.h"
#include<QDebug>
extern Scene10 *scene10;
GameEnemy::GameEnemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //set random x position
    int random_number = rand() % 10;
    setPos(random_number*50+150,0);

    // drew the rect
    setPixmap(QPixmap(":/images/images/wall1.png"));
    setScale(0.5);
    setTransformOriginPoint(25,25);

    connect(this,SIGNAL(gameover()),scene10,SLOT(reset()));

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(timer,SIGNAL(timeout()),this,SLOT(detect()));

    // start the timer
    timer->start(30);
}

void GameEnemy::move()
{

    setPos(x(),y()+5);
    if (pos().y() > 600){


        scene10->removeItem(this);
        delete this;}

}

void GameEnemy::detect()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if(dynamic_cast<Player*>(colliding_items[i])){
           qDebug()<<"boom";
           emit gameover();
           return;}
        else{continue;}
}

    return;
}
