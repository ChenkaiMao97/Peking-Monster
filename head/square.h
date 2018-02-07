#ifndef SQUARE_H
#define SQUARE_H

#include"mytimer.h"
#include<QGraphicsRectItem>
#include<QMouseEvent>
#include<QObject>
#include<QBrush>
#include<QGraphicsSceneMouseEvent>
class Square:public QObject, public QGraphicsRectItem
{Q_OBJECT
public:
    Square();
//public member function
    void changeColorMode();
    void backToNormal();
    void lighter();
//events
  //void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

  bool getS_shining() const;
  void setS_shining(bool value);

public slots:
  void setChangeColor();
  void setSquareColor();
signals:
  void ToBS_changeColorMode(int,int,int);

private:
    bool S_shining;
    QColor square_Color;
    QBrush Square_brush;
    Mytimer *timer1;
//    QTimer *timer2;
//    QTimer *timer3;
};

#endif // SQUARE_H
