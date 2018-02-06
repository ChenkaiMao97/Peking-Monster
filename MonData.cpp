#include"MonData.h"
#include<cstdlib>
#include<cmath>
#include<QBrush>
#include<QDebug>
using namespace std;
mon::mon(MonsterIcon *mon_MonsterICdefault, QString _name, int basicFullBlood, int basicFullPower, class skill *skillA, class skill *skillB, int basicFullExperienceValue, int bagNumber, int level)
{
	name = _name;
	basic_full_blood = basicFullBlood; basic_full_power = basicFullPower;
	skill[0] = skillA; skill[1] = skillB; _bagNumber = bagNumber; _level = level;
	_blood = (int)(basicFullBlood*pow((double)level,POWERINDEX));
	_power = (int)(basicFullPower*pow((double)level,POWERINDEX));//血量和能力值均以指数POWERINDEX增长
	basic_full_experience_value = basicFullExperienceValue; experience_value = 0;
	_survive = true;
    mon_MonsterIcon = mon_MonsterICdefault;

    mon_HPBar = new Bar(75,basicFullBlood,Qt::red);
    mon_MPBar = new Bar(75,basicFullPower,Qt::blue);
    mon_ExpBar = new Bar(75,basicFullExperienceValue,Qt::green);
}
mon::mon(const mon& m, int level)
{
    *this = m;
    setLevel(level);
}

QString mon::monName()const{return name;}
int mon::fullBlood()const{return (int)(basic_full_blood*pow((double)_level,POWERINDEX));}//血量以指数POWERINDEX增长
int mon::blood()const{return _blood>=0?_blood:0;}
int mon::fullPower()const{return (int)(basic_full_power*pow((double)_level,POWERINDEX));}//能力值以指数POWERINDEX增长
int mon::power()const{return _power;}
void mon::adBlood(unsigned int b)
{
	int f = fullBlood();
	_blood = (_blood+b)<=f?(_blood+b):f;
}
void mon::deBlood(unsigned int b){_blood = (_blood-b)>=0?(_blood-b):0;}
void mon::adPower(unsigned int p)
{
    int f = fullPower(), i = _power+p;
    _power = i<=f?i:f;
}
void mon::dePower(unsigned int p){int i = _power-p; _power = i>=0?i:0;}
int mon::level() const{return _level;}
void mon::adLevel(int extraExperienceValue)
{
	_level++;
	_blood = fullBlood();//每次升级时血量与能力值均恢复为满值
	_power = fullPower();
	experience_value = extraExperienceValue;//加上额外经验值
}
void mon::setLevel(int lev){_level = lev; upgrade();}
double mon::distance(int i)const{return skill[i-1]->distance();}
int mon::bagNumber()const{return _bagNumber;}
void mon::setBagNumber(int i){_bagNumber = i;}
int mon::fullExperienceValue()const{return (int)(basic_full_experience_value*pow((double)_level,FULLEXPINDEX));}//经验满值以指数EXPERIENCEINDEX增长
int mon::experienceValue()const{return experience_value;}
void mon::adExperienceValue(int exp)
{
	experience_value += exp;
	int i = fullExperienceValue();
	while(experience_value >= i){adLevel(experience_value-i);}
}
void mon::setExperienceValue(int exp){adExperienceValue(exp-experience_value);}

QString mon::skillName(int i)const{return skill[i-1]->skillName();}
int mon::aveDamage(int i)const{return (int)(skill[i-1]->basicDamage()*pow((double)_level,BATTLEINDEX));}//攻击值以指数BATTLEINDEX增长
int mon::avePowerConsumption(int i)const{return (int)(skill[i-1]->basicPowerConsumption()*pow((double)_level,BATTLEINDEX));}//能力值消耗以指数BATTLEINDEX增长
void mon::changeSkillA(class skill *skillA){skill[0] = skillA;}
void mon::changeSkillB(class skill *skillB){skill[1] = skillB;}

void mon::upgrade()
{
    skill[0]->upgrade(_level);
    skill[1]->upgrade(_level);
    _blood = fullBlood();
    _power = fullPower();
    _survive = true;
}
bool mon::survive()const{return _survive;}
void mon::setSurvive(bool s){_survive = s;}

monInBattle::monInBattle(int i)
{
    number = i;
    switch(i)
    {case 0:coordinate[0] = coordinate[1] = 0;break;
    case 1:coordinate[0] = coordinate[1] = 1;break;
    case 2:coordinate[0] = SIZE; coordinate[1] = 1;break;
    case 3:coordinate[0] = coordinate[1] = SIZE;break;
    case 4:coordinate[0] = 1; coordinate[1] = SIZE;break;
    }
}

monInBattle::monInBattle(MonsterIcon* MIC, QString _name, int basicFullBlood, int basicFullPower, class skill *skillA, class skill *skillB, int basicFullExperienceValue, int bagNumber, int level):
    mon(MIC,_name,basicFullBlood,basicFullPower,skillA,skillB,basicFullExperienceValue,bagNumber,level)
{number = coordinate[0] = coordinate[1] = 0;}

void monInBattle::setCoordinate(int cx, int cy)
{
    coordinate[0]=cx;
    coordinate[1]=cy;
}

monInBattle transMon(mon& m, const monInBattle& m0)
{
    monInBattle mib(m.mon_MonsterIcon,m.name,m.basic_full_blood,m.basic_full_power,m.skill[0],m.skill[1],m.basic_full_experience_value,m._bagNumber,m._level);
    mib._blood = m._blood; mib._power = m._power; mib._survive = m._survive;
    mib.mon_MonsterIcon=m.mon_MonsterIcon;
    mib.number = m0.number; mib.coordinate[0] = m0.coordinate[0];
	mib.coordinate[1] = m0.coordinate[1];
	mib.origin = &m;
	return mib;
}
int monInBattle::realDamage(int i)
{
	int sign = -1+2*(rand()%2);
	int random = rand();
	double variationRate = (random%100)*pow((double)_level,BATTLEINDEX)/100;
	return (int)(aveDamage(i)*(1+sign*skill[i-1]->fluctuationRate()*variationRate));
}
int monInBattle::realPowerConsumption(int i)
{
	int sign = -1+2*(rand()%2);
	int random = rand();
	double variationRate = (random%100)*pow((double)_level,BATTLEINDEX)/100;
	return (int)(avePowerConsumption(i)*(1+sign*skill[i-1]->fluctuationRate()*variationRate));
}
void monInBattle::kill(){_survive = false; coordinate[0] = coordinate[1] = (int)(SIZE/2); deBlood(blood());}

Bar::Bar(int fullLength, int fulldefault , QColor color)
{
    bar_timer= new Mytimer();
    setRect(0,0,fullLength,4);
    setfullValue(fulldefault);
    value=fulldefault/2;
    valueBar=new QGraphicsRectItem(this);
    int a = static_cast<int>(static_cast<double>(value)/static_cast<double>(fulldefault)*(this->rect().width()));
    valueBar->setRect(0,0,a,4);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    valueBar->setBrush(brush);
    //valueBar->setParentItem(this);

}

void Bar::setfullValue(int f)
{
    fullValue=f;
}

void Bar::setvalue(int v)
{
    value=v;
}

void Bar::advalue(int ad)
{
    value += ad;
    value= value<0 ? 0: value>fullValue? fullValue:value;
}

void Bar::devalue(int de)
{
    value -= de;
    value= value<0 ? 0: value>fullValue? fullValue:value;
}



void Bar::animateChange(int before, int after)
{   int be=before<0? 0: before>fullValue? fullValue:before;
    int af=after<0? 0: after>fullValue? fullValue:after;
    setvalue(af);
    if(be==af){return;}

    lengthBefore = static_cast<double>(be)/static_cast<double>(fullValue)*(this->rect().width());
    lengthAfter = static_cast<double>(af)/static_cast<double>(fullValue)*(this->rect().width());

    bar_timer->settimes(0);
    bar_timer->setInterval(50);
    bar_timer->start();
    connect(bar_timer,SIGNAL(timeout()),this,SLOT(setlength()));
}

void Bar::displayValue()
{
   int _width = static_cast<int>(static_cast<double>(value)/static_cast<double>(fullValue) * this->rect().width());
   valueBar->setRect(valueBar->x(),valueBar->y(),_width<1?1:_width,4);
}

void Bar::setlength()
{
    bar_timer->addtimes(20);   
    if(bar_timer->gettimes()==0)
    {
     bar_timer->stop();
     bar_timer->disconnect();
     return;
    }
    int length=lengthBefore+(bar_timer->gettimes()+1)*(lengthAfter-lengthBefore)/20;
    valueBar->setRect(0,0,length,valueBar->rect().height());
}
