#include"Battle.h"
#include<QDebug>
#include"battlescene.h"
void monOperation(initialSituation& iS, int number, int move, int attack)
{
    if(number<=0||number>6){qDebug()<<"mIB_onstage_Number error";return;}
    monInBattle* m1 = iS.b[number-1];
    switch(move){
    case 1:break;
    case 2:m1->coordinate[0]--;break;
    case 3:m1->coordinate[0]++;break;
    case 4:m1->coordinate[1]++;break;
    case 5:m1->coordinate[1]--;break;
    default:qDebug()<<"moveNumber error;";return;};

    monInBattle* m2;
    if(number==1||number==2)
        if(attack!=1){m2 = iS.b[(int)(attack/2)+1];}
        else m2 = new monInBattle;
    else if(number==3||number==4)
        if(attack!=1){m2 = iS.b[(int)(attack/2)-1];}
        else m2 = new monInBattle;
    switch(attack){
    case 1:break;
    case 2:
    case 4:m2->deBlood(m1->realDamage(1));m1->dePower(m1->realPowerConsumption(1));m1->deBlood(m2->blood()/10);break;
    case 3:
    case 5:m2->deBlood(m1->realDamage(2));m1->dePower(m1->realPowerConsumption(2));m1->deBlood(m2->blood()/10);break;
    default:qDebug()<<"attackNumber error";break;};

    if(m1->blood()==0)m1->kill();
    if(m2->blood()==0)m2->kill();
}
