#ifndef MONSTER_H
#define MONSTER_H

#include<QGraphicsPixmapItem>
#include<QObject>
#include"MonData.h"
#include"mytimer.h"
#include"tag.h"


class mon;
class Tag;
class Monster:public QObject,public QGraphicsPixmapItem//这个是毛超的图像monster
{Q_OBJECT
public:
  Monster();

  //member function
  void changeColorMode();
  void clearChangeColorMode();
  void changeRedMode();
  void clearChangeRedMode();
  void setInitial();

  QImage setBrightness(QImage& source, int factor);
  QImage setRedish(QImage& source, int factor);
  class Bar* Monster_HPBar=0;
  Bar* Monster_MPBar=0;
  //public attributes
  int monNumber=0;
  //getters and setters
  bool getM_shining() const;
  void setM_shining(bool value);

  bool getM_moved() const;
  void setM_moved(bool value);

  bool getM_owned() const;
  void setM_owned(bool value);

  bool getM_Redding() const;
  void setM_Redding(bool value);

  bool getM_alldone() const;
  void setM_alldone(bool value);

  int getMIBnumber() const;
  void setMIBnumber(int value);

  bool getHasBeenAdded() const;
  void setHasBeenAdded(bool value);

  QPixmap getmon_Pixmap();
  void setmon_Pixmap(QString mon_pm);
public slots:
  void setChangeColor();
  void setChangeRed();
private:
  bool M_shining=0;
  bool M_Redding=0;
  bool M_moved=0;
  bool M_alldone=0;
  bool M_owned=0;
  bool hasBeenAdded=0;
  int MIBnumber; //0,1,2,3
  QPixmap mon_Pixmap;
  Mytimer * mon_Timer;

};
//********************************************//这个是鸿丞聚聚的数据mon

//********************************************
class MonsterIcon:public QObject,public QGraphicsPixmapItem
{Q_OBJECT
public:
    MonsterIcon();

//member function
    void changeColorMode();
    void clearChangeColorMode();
    QImage setBrightness(QImage& source, int factor);
    QImage setGray(QImage& source);
    void setIconColor();
//public attributes
    QPixmap Icon_Pixmap=QPixmap();
    QPixmap Icon_GrayPixmap=QPixmap();
    Mytimer* icon_Timer;
    Monster* Icon_Monster=NULL;
    Tag* Icon_Tag=NULL;

    int monNumber=0;
    void setmonNumber(int n);
//events:
 void mousePressEvent(QGraphicsSceneMouseEvent *event);
 void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
 void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
 bool getIcon_Shining() const;
 void setIcon_Shining(bool value);

public slots:
 void setChangeColor();

private:
 bool Icon_shining=0;
};

class PhysicsMon:public Monster
{public:
    PhysicsMon();
};

class PhysicsMonIcon:public MonsterIcon
{
public:
    PhysicsMonIcon();
};

class MathMon:public Monster
{public:
    MathMon();
};
class MathMonIcon:public MonsterIcon
{
public:
    MathMonIcon();
};

class EnglishMon:public Monster
{public:
    EnglishMon();
};

class EnglishMonIcon:public MonsterIcon
{
public:
    EnglishMonIcon();
};

class PoliticsMon:public Monster
{public:
    PoliticsMon();
};

class PoliticsMonIcon:public MonsterIcon
{
public:
    PoliticsMonIcon();
};




#endif // MONSTER_H
