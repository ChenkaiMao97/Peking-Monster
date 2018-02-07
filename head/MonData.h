#ifndef MONDATA_H
#define MONDATA_H

#include"Skill.h"
#include"monster.h"
#include"mytimer.h"
class Bar:public QObject,public QGraphicsRectItem
{Q_OBJECT
public:
   Bar(){bar_timer= new Mytimer();valueBar=new QGraphicsRectItem();}
   Bar(int fullLength,int fulldefault ,QColor color);
//public attributes
   QGraphicsRectItem * valueBar;
   int fullValue;
   int value;
   int lengthBefore;
   int lengthAfter;
   Mytimer* bar_timer;
//member function
   void setfullValue(int f);
   void setvalue(int v);
   void advalue(int ad);
   void devalue(int de);
   void animateChange(int before,int after);
   void displayValue();

public slots:
   void setlength();
};

class monInBattle;
class mon
{
protected:
    QString name;
	int basic_full_blood, _blood;
	int basic_full_power, _power;
	skill *skill[2];
	int basic_full_experience_value, experience_value;
    int _bagNumber;//怪兽在背包中的序号
	int _level;
	bool _survive;
public:
    mon(){}
    //mon(mon& copyMon);
    mon(class MonsterIcon* mon_MonsterICdefault,QString,int,int,class skill*,class skill*,int,int=0,int=1);
    mon(const mon&,int);
    Bar* mon_HPBar;
    Bar* mon_MPBar;
    Bar* mon_ExpBar;
    class MonsterIcon* mon_MonsterIcon=NULL;
    QString monName()const;
	int fullBlood()const;
	int blood()const;
	void adBlood(unsigned int);
	void deBlood(unsigned int);
	int fullPower()const;
	int power()const;
	void adPower(unsigned int);
	void dePower(unsigned int);

	int fullExperienceValue()const;
	int experienceValue()const;
	void adExperienceValue(int);
	void setExperienceValue(int);

	int bagNumber()const;
	void setBagNumber(int);
	
    int level() const;
    void adLevel(int=0/*多余经验值*/);
	void setLevel(int);
    double distance(int/*技能序号*/)const;

    QString skillName(int/*技能序号*/)const;
    int aveDamage(int/*技能序号*/)const;
    int avePowerConsumption(int/*技能序号*/)const;
    void changeSkillA(class skill*);//用以换技能
	void changeSkillB(class skill*);

    void upgrade();

	bool survive()const;
	void setSurvive(bool);

	friend monInBattle transMon(mon&, const monInBattle&);
};

class monInBattle:public mon
{
public:
    int number;//战斗成员编号1、2、3、4，1、2为玩家，3、4为电脑
	int coordinate[2];
	mon* origin;

    monInBattle(int=0);
    monInBattle(MonsterIcon* MIC,QString, int basicFullBlood, int, /* int,*/ class skill*, class skill*, int=100, int=0, int=1);//初始构造与mon相同，故number与coordinate需要单独初始化
    void setCoordinate(int cx,int cy);
    int realDamage(int);
    int realPowerConsumption(int);//考虑了随机变动的战斗参数
	void kill();
    friend monInBattle transMon(mon&, const monInBattle&);
};
monInBattle transMon(mon&, const monInBattle& = monInBattle());//战斗之间将mon改造成monInBattle

#endif
