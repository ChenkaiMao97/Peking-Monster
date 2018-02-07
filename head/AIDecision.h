#ifndef AIDECISION_H
#define AIDECISION_H
#include"MonData.h"

class initialSituation;
class finalDecision//用以表示最终的AI决策
{
public:
    monInBattle b1, b2, b3, b4;//此仍为决策之前的战斗状态
    int move1, attack1, move2, attack2;//此均是指b3和b4的行动
    int attackOrder;//0为顺序，1为逆序
    finalDecision(){}
    finalDecision(const monInBattle&,const monInBattle&,const monInBattle&,const monInBattle&,int=1,int=1,int=1,int=1,int=0);
    void turn();//攻守状态对易
    void convert(const initialSituation&);
};
class initialSituation//用以表示当前战斗状态以便决策
{
public:
    monInBattle *b[4];
    initialSituation(){}
    initialSituation(monInBattle*, monInBattle*, monInBattle*, monInBattle*);
    void turn();
    void convert(const finalDecision&);//将最终决策转换为下一次的初始状态
};
finalDecision AIDecision(const initialSituation&);//由初始状态得到最终决策的方法
bool verify(const finalDecision&);//用以在战斗中检验用户的输入
#endif
