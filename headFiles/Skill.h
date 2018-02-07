#ifndef SKILL_H
#define SKILL_H

#include"Constant.h"
#include"stdio.h"
#include<QString>
class skill
{
private:
        QString name;
	int basic_damage;
	int basic_power_consumption;
        double _fluctuationRate;//只是一个比例0到1之间
        int _upgrade;
        double _distance=1.0;
        skill* nextLevel;
public:
	skill(){}
        skill(QString,int,int,double=0.0,double=1.0,skill* = NULL,int=0);
        QString skillName()const;
	int basicDamage()const;
	int basicPowerConsumption()const;
        double fluctuationRate()const;
        double distance()const;
        void upgrade(int level);
};

class superSkill
{
protected:
        QString name;
	int _parameter;
	float _fluctuationRate;//只是一个比例0到1之间
        int _category;
public:
	superSkill(){}
        superSkill(QString,int,float=0.0,int=1);
        QString superSkillName()const;
	int parameter()const;
	float fluctuationRate()const;
        int category()const;
};

#endif
