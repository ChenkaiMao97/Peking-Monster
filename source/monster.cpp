#include"monster.h"
#include"myview.h"
#include"battlescene.h"
#include<QPixmap>
#include<QImage>
#include<QString>
#include<QDebug>

extern Myview*view;
Monster::Monster()
{
    mon_Timer=new Mytimer();
    setScale(0.75);
    Monster_HPBar = new Bar(75,10,Qt::red);
    Monster_HPBar->setParentItem(this);
    Monster_HPBar->setPos(this->boundingRect().width()/2-Monster_HPBar->rect().width()/2+50,2);
    Monster_MPBar = new Bar(75,10,Qt::blue);
    Monster_MPBar->setParentItem(this);
    Monster_MPBar->setPos(this->boundingRect().width()/2-Monster_MPBar->rect().width()/2+50,8);
}

void Monster::changeColorMode()
{
    setM_shining(true);
    mon_Timer->settimes(0);
    mon_Timer->setInterval(50);
    mon_Timer->start();
    connect(mon_Timer,SIGNAL(timeout()),this,SLOT(setChangeColor()));
}

void Monster::clearChangeColorMode()
{
    setM_shining(false);
    mon_Timer->stop();
    setPixmap(getmon_Pixmap());
    disconnect(mon_Timer,SIGNAL(timeout()),this,SLOT(setChangeColor()));
}

void Monster::changeRedMode()
{
    qDebug()<<"change red";
    setM_Redding(true);
    mon_Timer->settimes(0);
    mon_Timer->setInterval(50);
    mon_Timer->start();
    connect(mon_Timer,SIGNAL(timeout()),this,SLOT(setChangeRed()));
}

void Monster::clearChangeRedMode()
{
    setM_Redding(false);
    mon_Timer->stop();
    setPixmap(getmon_Pixmap());
    //disconnect(mon_Timer,SIGNAL(timeout()),this,SLOT(setChangeRed()));
    mon_Timer->disconnect();
}

void Monster::setInitial()
{
    hasBeenAdded=false;
    M_alldone=false;M_moved=false;
    M_shining=false;M_Redding=false;
}

QPixmap Monster::getmon_Pixmap()
{
    return mon_Pixmap;
}

void Monster::setmon_Pixmap(QString mon_pm)
{
    mon_Pixmap=QPixmap(mon_pm);
}

QImage Monster::setBrightness(QImage& source, int factor)
{

        if (factor < -255 || factor > 255)
            return source;

        int red, green, blue;
        int pixels = source.width() * source.height();
        unsigned int *data = (unsigned int *)source.bits();
        for (int i = 0; i < pixels; ++i)
        {
            red= qRed(data[i])+ factor;
            red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
            green= qGreen(data[i])+factor;
            green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
            blue= qBlue(data[i])+factor;
            blue =  (blue  < 0x00) ? 0x00 : (blue  > 0xff) ? 0xff : blue ;
            data[i] = qRgba(red, green, blue, qAlpha(data[i]));
        }
        return source;

}

QImage Monster::setRedish(QImage &source, int factor)
{
    if (factor < -255 || factor > 255)
        return source;

    int red, green, blue;
    int pixels = source.width() * source.height();
    unsigned int *data = (unsigned int *)source.bits();
    for (int i = 0; i < pixels; ++i)
    {
        red= qRed(data[i])+ 5*factor;
        red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
        green= qGreen(data[i])-2*factor;
        green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
        blue= qBlue(data[i])-2*factor;
        blue =  (blue  < 0x00) ? 0x00 : (blue  > 0xff) ? 0xff : blue ;
        data[i] = qRgba(red, green, blue, qAlpha(data[i]));
    }
    return source;
}

void Monster::setChangeColor()
{
    mon_Timer->addtimes(20);
    int t= mon_Timer->gettimes()*50;
    int bm=50;
    double a = static_cast<double>(bm)/static_cast<double>(500*500);
    int bright = a*t*(1000-t);
    QImage old_image = mon_Pixmap.toImage();
    QImage new_image = setBrightness(old_image,bright);
    setPixmap(QPixmap::fromImage(new_image));
}

void Monster::setChangeRed()
{
    mon_Timer->addtimes(20);
    int t= mon_Timer->gettimes()*50;
    int rm=50;
    double a = static_cast<double>(rm)/static_cast<double>(500*500);
    int red = a*t*(1000-t);
    QImage old_image = mon_Pixmap.toImage();
    QImage new_image = setRedish(old_image,red);
    setPixmap(QPixmap::fromImage(new_image));
}

bool Monster::getHasBeenAdded() const
{
    return hasBeenAdded;
}

void Monster::setHasBeenAdded(bool value)
{
    hasBeenAdded = value;
}

int Monster::getMIBnumber() const
{
    return MIBnumber;
}

void Monster::setMIBnumber(int value)
{
    MIBnumber = value;
}

bool Monster::getM_alldone() const
{
    return M_alldone;
}

void Monster::setM_alldone(bool value)
{
    M_alldone = value;
}


bool Monster::getM_Redding() const
{
    return M_Redding;
}

void Monster::setM_Redding(bool value)
{
    M_Redding = value;
}

bool Monster::getM_owned() const
{
    return M_owned;
}

void Monster::setM_owned(bool value)
{
    M_owned = value;
}

bool Monster::getM_moved() const
{
    return M_moved;
}

void Monster::setM_moved(bool value)
{
    M_moved = value;
}

bool Monster::getM_shining() const
{
    return M_shining;
}

void Monster::setM_shining(bool value)
{
    M_shining = value;
}


void MonsterIcon::changeColorMode()
{
    icon_Timer->settimes(0);
    icon_Timer->setInterval(50);
    icon_Timer->start();
    connect(icon_Timer,SIGNAL(timeout()),this,SLOT(setChangeColor()));
    setIcon_Shining(true);
}

void MonsterIcon::clearChangeColorMode()
{
    icon_Timer->stop();
    setPixmap(Icon_Pixmap);
    disconnect(icon_Timer,SIGNAL(timeout()),this,SLOT(setChangeColor()));
    setIcon_Shining(false);
}

QImage MonsterIcon::setBrightness(QImage &source, int factor)
{

    if (factor < -255 || factor > 255)
        return source;

    int red, green, blue;
    int pixels = source.width() * source.height();
    unsigned int *data = (unsigned int *)source.bits();
    for (int i = 0; i < pixels; ++i)
    {
        red = qRed(data[i])+ factor;
        red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
        green = qGreen(data[i])+factor;
        green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
        blue = qBlue(data[i])+factor;
        blue = (blue  < 0x00) ? 0x00 : (blue  > 0xff) ? 0xff : blue ;
        data[i] = qRgba(red, green, blue, qAlpha(data[i]));
    }
    return source;
}

QImage MonsterIcon::setGray(QImage &source)
{
    int red;
    int pixels = source.width() * source.height();
    unsigned int *data = (unsigned int *)source.bits();
    for (int i = 0; i < pixels; ++i)
    {
        red = qRed(data[i]);
        data[i] = qRgba(red+100, red+100, red+100, qAlpha(data[i]));
    }
    return source;
}

void MonsterIcon::setIconColor()
{
    if(!view->view_hero->Mon(monNumber)->survive())
    {
        setPixmap(Icon_GrayPixmap);
    }
    else{setPixmap(Icon_Pixmap);}

}

void MonsterIcon::setmonNumber(int n)
{
    monNumber=n;
}

void MonsterIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    clearChangeColorMode();
}

void MonsterIcon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(dynamic_cast<BattleScene*>(view->scene()))
    {
      if(dynamic_cast<BattleScene*>(view->scene())->getStage_ButtonOnly())
      {
          Icon_Tag->tag_update();
          view->scene()->addItem(Icon_Tag);
          if(event->scenePos().x()+Icon_Tag->rect().width() > view->scene()->width())
          {
            Icon_Tag->setPos(view->scene()->width()-Icon_Tag->rect().width(),event->scenePos().y());
          }
          else
          {Icon_Tag->setPos(event->scenePos().x(),event->scenePos().y());}

          return;
      }
      else{return;}
    }
    else{return;}
}

void MonsterIcon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(dynamic_cast<BattleScene*>(view->scene()))
    {
      if(dynamic_cast<BattleScene*>(view->scene())->getStage_ButtonOnly())
      {
        view->scene()->removeItem(Icon_Tag);
        return;
      }
      else{return;}
    }
    else{return;}
}

void MonsterIcon::setChangeColor()
{
    icon_Timer->addtimes(20);
    int t= icon_Timer->gettimes()*50;
    int bm=30;
    double a = static_cast<double>(bm)/static_cast<double>(500*500);
    int bright = a*t*(1000-t);
    QImage old_image = Icon_Pixmap.toImage();
    QImage new_image = setBrightness(old_image,bright);
    setPixmap(QPixmap::fromImage(new_image));
}

bool MonsterIcon::getIcon_Shining() const
{
    return Icon_shining;
}

void MonsterIcon::setIcon_Shining(bool value)
{
    Icon_shining = value;
}

MonsterIcon::MonsterIcon()
{
    icon_Timer = new Mytimer();
    setAcceptHoverEvents(true);

}

PhysicsMon::PhysicsMon()
{   Monster::Monster();
    setmon_Pixmap(":/images/images/mon1.png");
    setPixmap(getmon_Pixmap());
    setScale(0.75);
}

PhysicsMonIcon::PhysicsMonIcon():MonsterIcon()
{
 Icon_Pixmap = QPixmap(":/images/images/monIcon1.png");
 setPixmap(Icon_Pixmap);
 QImage pixImage = Icon_Pixmap.toImage();
 QImage newImage = setGray(pixImage);
 Icon_GrayPixmap = QPixmap::fromImage(newImage);

 Icon_Monster = new PhysicsMon();
 setScale(0.75);
}

MathMon::MathMon()
{
    Monster::Monster();
    setmon_Pixmap(":/images/images/mon2.png");
    setPixmap(getmon_Pixmap());
    setScale(0.75);
}

MathMonIcon::MathMonIcon():MonsterIcon()
{

    Icon_Pixmap = QPixmap(":/images/images/monIcon2.png");
    setPixmap(Icon_Pixmap);
    QImage pixImage = Icon_Pixmap.toImage();
    QImage newImage = setGray(pixImage);
    Icon_GrayPixmap = QPixmap::fromImage(newImage);
    Icon_Monster = new MathMon();
    setScale(0.75);
}

EnglishMon::EnglishMon()
{
    Monster::Monster();
    setmon_Pixmap(":/images/images/mon3.png");
    setPixmap(getmon_Pixmap());
    setScale(0.75);
}

EnglishMonIcon::EnglishMonIcon():MonsterIcon()
{
    Icon_Pixmap = QPixmap(":/images/images/monIcon3.png");
    setPixmap(Icon_Pixmap);
    QImage pixImage = Icon_Pixmap.toImage();
    QImage newImage = setGray(pixImage);
    Icon_GrayPixmap = QPixmap::fromImage(newImage);
    Icon_Monster = new EnglishMon();
    setScale(0.75);
}

PoliticsMon::PoliticsMon()
{
    Monster::Monster();
    setmon_Pixmap(":/images/images/mon4.png");
    setPixmap(getmon_Pixmap());
    setScale(0.75);
}

PoliticsMonIcon::PoliticsMonIcon():MonsterIcon()
{
    Icon_Pixmap = QPixmap(":/images/images/monIcon4.png");
    setPixmap(Icon_Pixmap);
    QImage pixImage = Icon_Pixmap.toImage();
    QImage newImage = setGray(pixImage);
    Icon_GrayPixmap = QPixmap::fromImage(newImage);
    Icon_Monster = new PoliticsMon();
    setScale(0.75);
}


