#ifndef BUTTON_H
#define BUTTON_H

#include<QGraphicsRectItem>
#include<QObject>
#include<QGraphicsSceneMouseEvent>
class Button:public QObject, public QGraphicsRectItem
{Q_OBJECT
public:
    Button(int w, int h, QString text, QGraphicsItem *parent=NULL);
    QGraphicsTextItem *button_Text;
    void placetext();
    bool getHasBeenAdded() const;
    void add();
    void remove();
    void setColors(QColor c1,QColor c2);
    void setNormalColor();
    QColor button_ColorNormal=QColor();
    QColor button_ColorHover=QColor();
//event
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    bool hasBeenAdded=0;
signals:
    void clicked();

};

class SkillButton:public Button
{Q_OBJECT
public:
   SkillButton(int w, int h, QString text, QGraphicsItem *parent=NULL);
   int getSkillNumber() const;
   void setSkillNumber(int value);
   void setRed();
//event
       void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
       void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
       void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
       void clicked();
       void skillNumber(int n);
       void ToBS_skillSquareBack();

private:
 int skill_Number=0;

};

#endif // BUTTON_H
