#include<QPixmap>

#include"bulletin.h"


Bulletin::Bulletin()
{setPixmap(QPixmap(":/images/images/bulletin.png"));

}

void Bulletin::set_BulletinText(QString newbulletinText)
{
    bulletin_text=newbulletinText;
}

void Bulletin::setTextItem()
{
    textItemOfBulletin->
}
