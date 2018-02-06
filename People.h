#ifndef PEOPLE_H
#define PEOPLE_H

#include"AIDecision.h"
#include<QVector>
using namespace std;

class backpack
{
public:
    QVector<mon*> pocket;//千万注意，此处是以指针为挂件的
	int blood_pill_amount;
	int master_pill_amount;
	int poke_ball_amount;
	unsigned int _money;

	backpack(int=0,int=0,int=0,int=0);
	backpack(const mon&,const mon&,int=0,int=0,int=0,int=0);//初始化student
    backpack(const mon&, const mon&, const mon&, int=0, int=0, int=0, int money =0);//初始化character
};

class people
{
protected:
    QString name;
    backpack bag;
public:   
    people(){}
    people(QString,backpack);
    QString peopleName()const;

	int bloodPillAmount()const;
	int masterPillAmount()const;
	int pokeBallAmount()const;
    int size();
	mon* Mon(int/*怪物编号*/);//只能以指针传出才能修改数据,小心！！！

	unsigned int money()const;
};

class studentData:public people
{
protected:
	int _grade;
public:
	studentData(){}
    studentData(QString, backpack, int=1);
	int grade()const;
	void adGrade();
	void setGrade(int=1);
};

class characterData:public people
{
private:
	superSkill *Skill;
public:
	characterData(){}
    characterData(QString, backpack, superSkill*);
    QString superSkillName()const;
    int skillCategory()const;
	int realParameter()const;
};

class playerData:public studentData
{
private:
	int point;//与GPA相关的
public:
	playerData(){}
    playerData(QString, backpack, int=1, int=100);
	void changeMon(mon*,const mon&);

	void adBloodPill(int=1);
	void setBloodPill(int=0);
	void useBloodPill(mon*);

	void adMasterPill(int=1);
	void setMasterPill(int=0);
	void useMasterPill(mon*);

	void adPokeBall(int=1);
	void setPokeBall(int=0);
	bool usePokeBall(monInBattle*);//返回值表示怪物是否成功被捕

	void adMoney(unsigned int);
	void deMoney(unsigned int);

	double GPA()const;
	void deGPA(int);
	void setGPA(int=100);
};

#endif
