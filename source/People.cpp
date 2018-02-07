#include"People.h"
#include"stdlib.h"
#include<cmath>
#include<QDebug>
#include"stdio.h"
#include"MonData.h"

backpack::backpack(int bloodPillAmount, int masterPillAmount, int pokeBallAmount, int money)
{blood_pill_amount = bloodPillAmount; master_pill_amount = masterPillAmount; poke_ball_amount = pokeBallAmount; _money = money;}
backpack::backpack(const mon &m1, const mon &m2, int bloodPillAmount, int masterPillAmount, int pokeBallAmount, int money)
{
    blood_pill_amount = bloodPillAmount;
    master_pill_amount = masterPillAmount;
    poke_ball_amount = pokeBallAmount;
    _money = money;
	mon _m1 = m1, _m2 = m2;
    pocket.append(new mon(_m1));_m1.mon_MonsterIcon->setmonNumber(1);
    pocket.append(new mon(_m2));_m2.mon_MonsterIcon->setmonNumber(2);
}
backpack::backpack(const mon &m1, const mon &m2, const mon &m3, int bloodPillAmount, int masterPillAmount, int pokeBallAmount, int money)
{
    blood_pill_amount = bloodPillAmount; master_pill_amount = masterPillAmount; poke_ball_amount = pokeBallAmount; _money = money;
    mon _m1 = m1, _m2 = m2, _m3 = m3;
    pocket.append(new mon(_m1));
    pocket.append(new mon(_m2));
    pocket.append(new mon(_m3));
    for(size_t i=0,n=3;i<n;i++)
     {
        pocket[i]->mon_MonsterIcon->setmonNumber(i+1);
        pocket[i]->setBagNumber(i+1);
        pocket[i]->mon_MonsterIcon->Icon_Monster->monNumber=i+1;
     }
    return;
}

people::people(QString _name, backpack _bag)
{
    name = _name; bag = _bag;
    for(int i=0;i<bag.pocket.size();i++)
    {bag.pocket[i]->upgrade();}
}
QString people::peopleName()const{return name;}
int people::bloodPillAmount()const{return bag.blood_pill_amount;}
int people::masterPillAmount()const{return bag.master_pill_amount;}
int people::pokeBallAmount()const{return bag.poke_ball_amount;}

int people::size()
{
    return bag.pocket.size();
}
mon* people::Mon(int i){return bag.pocket[i-1];}
unsigned int people::money()const{return bag._money;}

studentData::studentData(QString _name, backpack _bag, int grade):people(_name, _bag),_grade(grade){}
int studentData::grade()const{return _grade;}
void studentData::adGrade(){_grade++;}
void studentData::setGrade(int i)
{
    if(i<1)_grade = 1;
    else if(i>4)_grade = 4;
    else _grade = i;
}

characterData::characterData(QString _name, backpack _bag, superSkill* _Skill):people(_name,_bag),Skill(_Skill){}
QString characterData::superSkillName()const{return Skill->superSkillName();}
int characterData::skillCategory()const{return Skill->category();}
int characterData::realParameter()const
{
	int sign = -1+2*(rand()%2);
	int random = rand();
	double variationRate = random%100;
	return (int)(Skill->parameter()*(1+sign*Skill->fluctuationRate()*variationRate));
}

playerData::playerData(QString _name, backpack _bag, int grade, int _point):studentData(_name,_bag,grade),point(_point){}
void playerData::changeMon(mon* m0, const mon& m)
{delete m0; m0 = new mon(m);}
void playerData::adBloodPill(int i){bag.blood_pill_amount += i;}
void playerData::setBloodPill(int i){bag.blood_pill_amount = i;}
void playerData::useBloodPill(mon* m)
{
	if(bag.blood_pill_amount >= 1)
	{
		bag.blood_pill_amount--;
		m->adBlood((int)(m->fullBlood()*PILLRATIO));
	}
}
void playerData::adMasterPill(int i){bag.master_pill_amount += i;}
void playerData::setMasterPill(int i){bag.master_pill_amount = i;}
void playerData::useMasterPill(mon* m)
{
	if(bag.master_pill_amount >= 1 && m->survive()==false)
	{
		bag.master_pill_amount--;
		m->setSurvive(true);
		m->adBlood(m->fullBlood());
		m->adPower(m->fullPower());
		m->setLevel(m->level()>1?(m->level()-1):1);//复活者降级
		m->setExperienceValue(0);
	}
}
void playerData::adPokeBall(int i){bag.poke_ball_amount += i;}
void playerData::setPokeBall(int i){bag.poke_ball_amount = i;}
bool playerData::usePokeBall(monInBattle* m)
{
    if(m->survive() && pokeBallAmount()>0 && m->blood()<(int)(m->fullBlood()/3) && bag.pocket.size()<(_grade*2))//只有在怪兽血量为满血的三分之一以下时才可出动精灵球
	{
		srand(time(0));
		int topLine = 33, bottomLine = (int)(100*m->blood()/m->fullBlood());
		int i = rand()%60;
		if(i>topLine||i<bottomLine)return false;
		else
		{
            bag.pocket.append(new mon(*m));
            int i = bag.pocket.size();
			bag.pocket[i-1]->setBagNumber(i);
			m->kill();
			return true;
		}
	}
	return false;
}
void playerData::adMoney(unsigned int i){bag._money += i;}
void playerData::deMoney(unsigned int i){bag._money -= i;}//使用前务必谨慎，钱数不可为负
double playerData::GPA()const{return pow(100.0-point,2)*(3/1600);}
void playerData::deGPA(int i){point = (point-i)>59?(point-i):59;}
void playerData::setGPA(int i){point = i;}
