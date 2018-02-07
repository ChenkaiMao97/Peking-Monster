#ifndef MYTEXTITEM_H
#define MYTEXTITEM_H

#include<QGraphicsTextItem>
#include<QVector>
#include<QString>
class TextInf
{
public:
    TextInf(){}
    TextInf(QString inf_Textdef, int inf_Hdef=-2);
    QString inf_Text;
    int inf_HeadNumber;
};

class MyTextItem:public QGraphicsTextItem
{
public:
    MyTextItem(QGraphicsItem *parent=0);
    QVector<TextInf>text;
    void addTextInf(TextInf newtext);
    int getSpeakTimes();
    void setNextToSay();
    TextInf getNextToSay();
    bool speakOver();
    bool getHasBeenAdded() const;
    void add();
    void remove();
protected:
    bool hasBeenAdded=0;
private:
    int counter;
    TextInf nextToSay;
};

#endif // MYTEXTITEM_H
