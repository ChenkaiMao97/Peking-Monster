#ifndef GAMEENEMY_H
#define GAMEENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class GameEnemy: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    GameEnemy(QGraphicsItem * parent=0);
public slots:
    void move();
    void detect();
signals:
    void gameover();
};


#endif // GAMEENEMY_H
