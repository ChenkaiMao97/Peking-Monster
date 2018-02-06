#include<QGraphicsTextItem>
#include<QBrush>
#include<QDebug>
#include"button.h"

Button::Button(int w,int h,QString text,QGraphicsItem *parent)
{  setRect(0,0,w,h);
   button_ColorNormal=Qt::darkCyan;
   button_ColorHover=Qt::cyan;
   QBrush brush;
   brush.setStyle(Qt::SolidPattern);
   brush.setColor(button_ColorNormal);
   setBrush(brush);

   button_Text = new QGraphicsTextItem(text,this);
   placetext();
   setAcceptHoverEvents(true);
}

void Button::placetext()
{
    int xPos = rect().width()/2-button_Text->boundingRect().width()/2;
    int yPos = rect().height()/2-button_Text->boundingRect().height()/2;
    button_Text->setPos(xPos,yPos);
}
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(button_ColorHover);
    setBrush(brush);
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(button_ColorNormal);
    setBrush(brush);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

bool Button::eventFilter(QObject *obj, QEvent *event)
{
qDebug()<<"hahah";
return QObject::eventFilter(obj, event);
}

void Button::add()
{
    hasBeenAdded = true;
}

void Button::remove()
{
    hasBeenAdded = false;
}

void Button::setColors(QColor c1, QColor c2)
{
    button_ColorNormal = c1;
    button_ColorHover = c2;
}

void Button::setNormalColor()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(button_ColorNormal);
    setBrush(brush);
}

bool Button::getHasBeenAdded() const
{
    return hasBeenAdded;
}


SkillButton::SkillButton(int w, int h, QString text, QGraphicsItem *parent):Button(w,h,text,parent)
{
}

void SkillButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Button::hoverEnterEvent(event);
    qDebug()<<"enter button";
    emit skillNumber(getSkillNumber());
}

void SkillButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Button::hoverLeaveEvent(event);
    emit ToBS_skillSquareBack();
}

void SkillButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

int SkillButton::getSkillNumber() const
{
    return skill_Number;
}

void SkillButton::setSkillNumber(int value)
{
    skill_Number = value;
}

void SkillButton::setRed()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(button_ColorNormal.red()-20,button_ColorNormal.green()+20,button_ColorNormal.blue()+20));
    setBrush(brush);
    return;
}
