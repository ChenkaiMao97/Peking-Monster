#include"Skill.h"

skill::skill(QString _name, int basicDamage, int basicPowerConsupmtion, double fluctuationRate, double distance, skill* _nextLevel, int upgrade)
{
        name = _name; basic_damage = basicDamage;
        basic_power_consumption = basicPowerConsupmtion;
        _fluctuationRate = fluctuationRate; _distance = distance;
        nextLevel = _nextLevel;
        _upgrade = upgrade;
}
QString skill::skillName()const{return name;}
int skill::basicDamage()const{return basic_damage;}
int skill::basicPowerConsumption()const{return basic_power_consumption;}
double skill::fluctuationRate()const{return _fluctuationRate;}
double skill::distance()const{return _distance;}
void skill::upgrade(int level)
{
     if(nextLevel!=NULL && level>=_upgrade)
             *this = *nextLevel;
}

superSkill::superSkill(QString _name, int Parameter, float fluctuationRate, int category):
name(_name),_parameter(Parameter),_fluctuationRate(fluctuationRate),_category(category){}
QString superSkill::superSkillName()const{return name;}
int superSkill::parameter()const{return _parameter;}
float superSkill::fluctuationRate()const{return _fluctuationRate;}
int superSkill::category()const{return _category;}
