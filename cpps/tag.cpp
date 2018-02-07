#include"tag.h"
#include"MonData.h"
#include<QString>
#include<QBrush>
#include<QDebug>
extern monInBattle* BS_monIB_PL;
Tag::Tag(monInBattle *MIBdefault)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(220,210,200));
    setBrush(brush);
    tag_MIB=MIBdefault;
    setRect(0,0,300,150);
    tag_HPbar=new Bar(120,tag_MIB->fullBlood(),Qt::red);     tag_HPbar->setParentItem(this);
    tag_MPbar=new Bar(120,tag_MIB->fullPower(),Qt::blue);      tag_MPbar->setParentItem(this);
    tag_Expbar=new Bar(120,tag_MIB->experienceValue(),Qt::green);     tag_Expbar->setParentItem(this);
    tag_Name.setPlainText(QString("Name : ").append(tag_MIB->monName()));     tag_Name.setParentItem(this);
    tag_description.setPlainText("balabala");     tag_description.setParentItem(this);
    tag_PixmapItem.setPixmap(tag_MIB->mon_MonsterIcon->Icon_Monster->getmon_Pixmap());tag_PixmapItem.setScale(0.75);    tag_PixmapItem.setParentItem(this);
    tag_Level.setPlainText(QString("Level : ").append(QString::number(tag_MIB->level())));     tag_Level.setParentItem(this);
    tag_HP.setPlainText(QString("HP : ").append(QString::number(tag_MIB->blood())).append("/").append(QString::number(tag_MIB->fullBlood())));     tag_HP.setParentItem(this);
    tag_MP.setPlainText(QString("MP : ").append(QString::number(tag_MIB->power())).append("/").append(QString::number(tag_MIB->fullPower())));     tag_MP.setParentItem(this);
    tag_Exp.setPlainText(QString("EXP : ").append(QString::number(tag_MIB->experienceValue())).append("/").append(QString::number(tag_MIB->fullExperienceValue())));     tag_Exp.setParentItem(this);
    tag_Skill1.setPlainText(QString("Skill1 : ").append(tag_MIB->skillName(1)));     tag_Skill1.setParentItem(this);
    tag_Skill2.setPlainText(QString("Skill2 : ").append(tag_MIB->skillName(2)));     tag_Skill2.setParentItem(this);
    setAllPos();

}

void Tag::tag_update()
{
    tag_Level.setPlainText(QString("Level : ").append(QString::number(tag_MIB->level())));
    tag_HP.setPlainText(QString("HP : ").append(QString::number(tag_MIB->blood())).append("/").append(QString::number(tag_MIB->fullBlood())));
    tag_HPbar->setvalue(tag_MIB->blood());tag_HPbar->setfullValue(tag_MIB->fullBlood());
    tag_HPbar->displayValue();
    tag_MP.setPlainText(QString("MP : ").append(QString::number(tag_MIB->power())).append("/").append(QString::number(tag_MIB->fullPower())));
    tag_MPbar->setvalue(tag_MIB->power());tag_MPbar->setfullValue(tag_MIB->fullPower());/*qDebug()<<tag_MIB->experienceValue();*/
    tag_MPbar->displayValue();
    tag_Exp.setPlainText(QString("EXP : ").append(QString::number(tag_MIB->experienceValue())).append("/").append(QString::number(tag_MIB->fullExperienceValue())));
    tag_Expbar->setvalue(tag_MIB->experienceValue()); tag_Expbar->setfullValue(tag_MIB->fullExperienceValue());qDebug()<<tag_MIB->experienceValue();
    tag_Expbar->displayValue();
    tag_Skill1.setPlainText(QString("Skill1 : ").append(tag_MIB->skillName(1)));
    tag_Skill2.setPlainText(QString("Skill2 : ").append(tag_MIB->skillName(2)));
}

void Tag::setAllPos()
{
    tag_PixmapItem.setPos(x(),y()+12);
    tag_Name.setPos(x()+70,y()+10);tag_Level.setPos(x()+180,y()+10);
    tag_HP.setPos(x()+70,y()+25);
    tag_MP.setPos(x()+70,y()+40);
    tag_Exp.setPos(x()+70,y()+55);
    int x1=tag_HP.pos().x()+tag_HP.boundingRect().width()-2;
    int x2=tag_MP.pos().x()+tag_MP.boundingRect().width()-2;
    int x3=tag_Exp.pos().x()+tag_Exp.boundingRect().width()-2;
    int xm=x1>x2? x1:x2;
    int xmreal= x3>xm ? x3:xm;
    tag_HPbar->setPos(xmreal,tag_HP.pos().y()+tag_HP.boundingRect().height()-14);
    tag_MPbar->setPos(xmreal,tag_MP.pos().y()+tag_MP.boundingRect().height()-14);
    tag_Expbar->setPos(xmreal,tag_Exp.pos().y()+tag_Exp.boundingRect().height()-14);
    tag_Skill1.setPos(x()+70,y()+70);
    tag_Skill2.setPos(x()+170,y()+70);
    tag_description.setPos(x()+10,y()+90);

}
