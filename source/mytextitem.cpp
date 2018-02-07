#include"mytextitem.h"
#include"button.h"
#include<QDebug>
#include<QFont>
#include<QEvent>
#include<QGraphicsSceneMouseEvent>
MyTextItem::MyTextItem(QGraphicsItem *parent)
{
    counter=0;
    QFont textFont("comic sans",20);
    setFont(textFont);
}

void MyTextItem::addTextInf(TextInf newtext)
{
    text.append(newtext);
}

int MyTextItem::getSpeakTimes()
{
    return text.size();
}

void MyTextItem::setNextToSay()
{
    nextToSay=text[counter];
    setPlainText(nextToSay.inf_Text);
    counter++;
    counter=counter%getSpeakTimes();
}

TextInf MyTextItem::getNextToSay()
{
    return nextToSay;
}


bool MyTextItem::speakOver()
{
    if (counter==0)return true;
    else return false;
}
void MyTextItem::add()
{
    hasBeenAdded = true;
}

void MyTextItem::remove()
{
    hasBeenAdded = false;
}

bool MyTextItem::getHasBeenAdded() const
{
    return hasBeenAdded;
}
//void MyTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug()<<"children accepted";
//    //dynamic_cast<Button*>(parent())->mousePressEvent(event);
//}


TextInf::TextInf(QString inf_Textdef, int inf_Hdef)
{
    inf_Text=inf_Textdef; inf_HeadNumber=inf_Hdef;
}
