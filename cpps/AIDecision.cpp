        #include"AIDecision.h"
    #include<cmath>
    using namespace std;

    initialSituation::initialSituation(monInBattle* _b1,monInBattle* _b2,monInBattle* _b3,monInBattle* _b4)
    {b[0] = _b1; b[1] = _b2; b[2] = _b3; b[3] = _b4;}
    void initialSituation::turn()
    {monInBattle* t; t=b[0];b[0]=b[2];b[2]=t; t=b[1];b[1]=b[3];b[3]=t;}
    void initialSituation::convert(const finalDecision& d)
    {b[0] = new monInBattle(d.b1); b[1] = new monInBattle(d.b2); b[2] = new monInBattle(d.b3); b[3] = new monInBattle(d.b4);}

    finalDecision::finalDecision(const monInBattle& _b1,const monInBattle& _b2,const monInBattle& _b3,const monInBattle& _b4,int _move1,int _attack1,int _move2,int _attack2,int _attackOrder)
    {b1 = _b1; b2 = _b2; b3 = _b3; b4 = _b4; move1 = _move1; attack1 = _attack1; move2 = _move2; attack2 = _attack2; attackOrder = _attackOrder;}
    void finalDecision::turn()
    {monInBattle t; t=b1;b1=b3;b3=t; t=b2;b2=b4;b4=t;}
    void finalDecision::convert(const initialSituation& s)
    {b1 = *s.b[0]; b2 = *s.b[1]; b3 = *s.b[2]; b4 = *s.b[3];}

    struct situation
    {
        monInBattle b1, b2, b3, b4;
        int firstStepDecision;
        int contemporaryStepDecision;
        int attackOrder;//0为1先攻，1为2先攻
        situation *former, *next;
    };

    bool verify(const situation *s, int move1, int move2, int attack1, int attack2)
    {
        monInBattle b1 = s->b1, b2 = s->b2, b3 = s->b3, b4 = s->b4;
        int x1 = b1.coordinate[0], y1 = b1.coordinate[1], x2 = b2.coordinate[0], y2 = b2.coordinate[1];
        int x3 = b3.coordinate[0], y3 = b3.coordinate[1], x4 = b4.coordinate[0], y4 = b4.coordinate[1];
    //判断能不能走
        if(b1.survive())
        {
        if(move1==2 && x1<=1)return false;
        else if(move1==3 && x1>=SIZE)return false;
        else if(move1==4 && y1>=SIZE)return false;
        else if(move1==5 && y1<=1)return false;
        }
        else if(move1!=1)return false;
        if(b2.survive())
        {
        if(move2==2 && x2<=1)return false;
        else if(move2==3 && x2>=SIZE)return false;
        else if(move2==4 && y2>=SIZE)return false;
        else if(move2==5 && y2<=1)return false;
        }
        else if(move2!=1)return false;

        if(move1==2)x1-=1;
        else if(move1==3)x1+=1;
        else if(move1==4)y1+=1;
        else if(move1==5)y1-=1;
        if(move2==2)x2-=1;
        else if(move2==3)x2+=1;
        else if(move2==4)y2+=1;
        else if(move2==5)y2-=1;
        if((x1==x2&&y1==y2&&b1.survive()&&b2.survive())||(x1==x3&&y1==y3&&b1.survive()&&b3.survive())||(x1==x4&&y1==y4&&b1.survive()&&b4.survive())||
            (x2==x4&&y2==y4&&b2.survive()&&b4.survive())||(x2==x3&&y2==y3&&b2.survive()&&b3.survive())||(x3==x4&&y3==y4&&b3.survive()&&b4.survive()))return false;
        //if(b1.survive()&&b2.survive()&&(x1==b2.coordinate[0]&&y1==b2.coordinate[1])&&(x2==b1.coordinate[0]&&y2==b1.coordinate[1]))return false;
    //判断能不能出击:
        if(b1.survive())
        {
            if(attack1==2||attack1==3)
            {
                if(b3.survive())
                {
                    if(b1.power()<b1.avePowerConsumption(attack1-1))return false;
                }
                else return false;
            }
            else if(attack1==4||attack1==5)
            {
                if(b4.survive())
                {
                    if(b1.power()<b1.avePowerConsumption(attack1-3))return false;
                }
                else return false;
            }
        }
        else if(attack1!=1)return false;
        if(b2.survive())
        {
            if(attack2==2||attack2==3)
            {
                if(b3.survive())
                {
                    if(b2.power()<b2.avePowerConsumption(attack2-1))return false;
                }
                else return false;
            }
            else if(attack2==4||attack2==5)
            {
                if(b4.survive())
                {
                    if(b2.power()<b2.avePowerConsumption(attack2-3))return false;
                }
                else return false;
            }
        }else if(attack2!=1)return false;

        monInBattle m1, m2;
        double d;
        if(attack1==2||attack1==3)
        {
            d = sqrt(pow((double)(x1-x3),2)+pow((double)(y1-y3),2));
            if(d > b1.distance(attack1-1))return false;
        }

        if(attack1==4||attack1==5)
        {
            d = sqrt(pow((double)(x1-x4),2)+pow((double)(y1-y4),2));
            if(d > b1.distance(attack1-3))return false;
        }
        if(attack2==2||attack2==3)
        {
            d = sqrt(pow((double)(x2-x3),2)+pow((double)(y2-y3),2));
            if(d > b2.distance(attack2-1))return false;
        }

        if(attack2==4||attack2==5)
        {
            d = sqrt(pow((double)(x2-x4),2)+pow((double)(y2-y4),2));
            if(d > b2.distance(attack2-3))return false;
        }

        return true;
    }

    situation proceed(const situation *s, int move1, int move2, int attack1, int attack2, int depth)
    {
        situation now = *s;
        if(depth==0)now.firstStepDecision = (((move1-1)*5+attack1)-1)*25+((move2-1)*5+attack2);
        now.contemporaryStepDecision = (((move1-1)*5+attack1)-1)*25+((move2-1)*5+attack2);
        now.former = now.next = NULL;
        int x2 = now.b2.coordinate[0], y2 = now.b2.coordinate[1];
        if(move1==2)(now.b1).coordinate[0] -= 1;
        else if(move1==3)(now.b1).coordinate[0] += 1;
        else if(move1==4)(now.b1).coordinate[1] += 1;
        else if(move1==5)(now.b1).coordinate[1] -= 1;
        if(move2==2)(now.b2).coordinate[0] -= 1;
        else if(move2==3)(now.b2).coordinate[0] += 1;
        else if(move2==4)(now.b2).coordinate[1] += 1;
        else if(move2==5)(now.b2).coordinate[1] -= 1;
        int order = 0;//默认1号先走
        if((now.b1).coordinate[0]==x2&&(now.b1).coordinate[1]==y2)order = 1;//2号先走
        now.attackOrder = order;

        if(attack1==2||attack1==3){now.b3.deBlood(now.b1.realDamage(attack1-1)); now.b1.dePower(now.b1.realPowerConsumption(attack1-1)); now.b1.deBlood((int)(now.b3.blood()/10));}
        else if(attack1==4||attack1==5){now.b4.deBlood(now.b1.realDamage(attack1-3)); now.b1.dePower(now.b1.realPowerConsumption(attack1-3)); now.b1.deBlood((int)(now.b4.blood()/10));}
        if(attack2==2||attack2==3){now.b3.deBlood(now.b2.realDamage(attack2-1)); now.b2.dePower(now.b2.realPowerConsumption(attack2-1)); now.b2.deBlood((int)(now.b3.blood()/10));}
        else if(attack2==4||attack2==5){now.b4.deBlood(now.b2.realDamage(attack2-3)); now.b2.dePower(now.b2.realPowerConsumption(attack2-3)); now.b2.deBlood((int)(now.b4.blood()/10));}

        if(now.b1.blood()==0)now.b1.kill();
        if(now.b2.blood()==0)now.b2.kill();
        if(now.b3.blood()==0)now.b3.kill();
        if(now.b4.blood()==0)now.b4.kill();

        return now;
    }

    int minValue(const monInBattle& b1, const monInBattle& b2, const monInBattle& b3, const monInBattle& b4)
    {
        int oppoDeBlood = (b3.fullBlood()-b3.blood())+(b4.fullBlood()-b4.blood());
        double oppoDeBloodRate = (b3.fullBlood()-b3.blood())/b3.fullBlood()+(b4.fullBlood()-b4.blood())/b4.fullBlood();
        int selfDeBlood1 = (b1.fullBlood()-b1.blood());
        double selfDeBloodRate1 = selfDeBlood1/b1.fullBlood();
        int selfDeBlood2 = (b2.fullBlood()-b2.blood());
        double selfDeBloodRate2 = selfDeBlood2/b2.fullBlood();
        int escapeSign1 = 1, escapeSign2 = 1;
        if(oppoDeBloodRate < selfDeBloodRate1+selfDeBloodRate2)
        {
            if(selfDeBloodRate1>selfDeBloodRate2)escapeSign1 = -1;
            if(selfDeBloodRate1<selfDeBloodRate2)escapeSign2 = -1;
        }
        int distance13 = abs(b1.coordinate[0]-b3.coordinate[0])+abs(b1.coordinate[1]-b3.coordinate[1]);
        int distance14 = abs(b1.coordinate[0]-b4.coordinate[0])+abs(b1.coordinate[1]-b4.coordinate[1]);
        int distance23 = abs(b2.coordinate[0]-b3.coordinate[0])+abs(b2.coordinate[1]-b3.coordinate[1]);
        int distance24 = abs(b2.coordinate[0]-b4.coordinate[0])+abs(b2.coordinate[1]-b4.coordinate[1]);
        return 100*(oppoDeBlood-selfDeBlood1-selfDeBlood2)-escapeSign1*(distance13+distance14)-escapeSign2*(distance23+distance24);
    }

    finalDecision AIDecision(const initialSituation& initialSituation)
    {
        int action1, action2, move1, move2, attack1, attack2, depth = 0, counter = 0;
        const monInBattle b3 = *initialSituation.b[0], b4 = *initialSituation.b[1], b1 = *initialSituation.b[2], b2 = *initialSituation.b[3];
        situation s0 = {b1,b2,b3,b4,1,1,0,NULL,NULL};
        situation *head = &s0, *headNext, *pointer, *pointerNext, *deleter, *assistant;
        situation preferable, temporary, optimum = {b3,b4,b1,b2,1,1,0,NULL,NULL};
        optimum.firstStepDecision = optimum.contemporaryStepDecision = 1;
        int optimumDecisionCode = 1, optimumAttackOrder = 0;

        while(depth<=DEP)
        {
    //开始绘制新列表:
        headNext = pointerNext = NULL;
        for(int i=0;i<625;i++)
        {
            action1 = ((i+1)%25==0)? ((i+1)/25) : (int)((i+1)/25+1); action2 = ((i+1)%25==0)? 25 : ((i+1)%25);
            move1 = (action1%5==0)? (action1/5) : (int)(action1/5+1); attack1 = (action1%5==0)? 5 : (action1%5);
            move2 = (action2%5==0)? (action2/5) : (int)(action2/5+1); attack2 = (action2%5==0)? 5 : (action2%5);
            pointer = head; preferable = *head;
            counter = 0;
            while(pointer != NULL)
            {
                if(verify(pointer,move1,move2,attack1,attack2))
                {
                    temporary = proceed(pointer,move1,move2,attack1,attack2,depth);
                    if(!temporary.b3.survive()&&!temporary.b4.survive() && depth%2==0)
                    {optimumDecisionCode = temporary.firstStepDecision; optimumAttackOrder = temporary.attackOrder; goto build;}

                    bool wideMove = (depth<=MIDDEP);
                    bool turnAggressive = (depth>MIDDEP && minValue(temporary.b1,temporary.b2,temporary.b3,temporary.b4) >= minValue(preferable.b1,preferable.b2,preferable.b3,preferable.b4));
                    if(wideMove)
                    {
                        monInBattle t;
                        t = temporary.b1; temporary.b1 = temporary.b3; temporary.b3 = t;
                        t = temporary.b2; temporary.b2 = temporary.b4; temporary.b4 = t;
                        if(headNext==NULL){pointerNext = headNext = new situation(temporary); pointerNext->former = pointerNext->next = NULL;}
                        else
                        {
                            assistant = pointerNext;
                            pointerNext = new situation(temporary);
                            pointerNext->former = assistant;
                            assistant->next = pointerNext;
                            pointerNext->next = NULL;
                        }
                    }
                    if(turnAggressive){preferable = temporary; counter++;}
                }
                pointer = pointer->next;
            }
            if(counter>0)
            {
                if(!preferable.b3.survive()&&!preferable.b4.survive() && depth%2==0)
                {optimumDecisionCode = preferable.firstStepDecision; optimumAttackOrder = preferable.attackOrder; goto build;}

                monInBattle t;
                t = preferable.b1; preferable.b1 = preferable.b3; preferable.b3 = t;
                t = preferable.b2; preferable.b2 = preferable.b4; preferable.b4 = t;
                if(head==NULL){pointerNext = headNext = new situation(preferable); pointerNext->former = pointerNext->next = NULL;}
                else
                {
                    assistant = pointerNext;
                    pointerNext = new situation(preferable);
                    pointerNext->former = assistant;
                    pointerNext->next = NULL;
                }
            }
        }
    //将前一列表清空，并移动至下一列表:
        if(head != &s0)
        {
            deleter = pointer = head;
            while(pointer != NULL)
            {
                pointer = pointer->next;
                delete deleter;
                deleter = pointer;
            }
        }
        head = headNext;
    //在AI新列表中寻找最优:
        if(depth%2==0)
        {
            pointer = head;
            while(pointer != NULL)
            {
                int a = minValue(pointer->b3,pointer->b4,pointer->b1,pointer->b2);
                int b = minValue(optimum.b3,optimum.b4,optimum.b1,optimum.b2);
                if(minValue(pointer->b3,pointer->b4,pointer->b1,pointer->b2) > minValue(optimum.b3,optimum.b4,optimum.b1,optimum.b2))
                    optimum = *pointer;
                pointer = pointer->next;
            }
        }
    //在敌方新列表中删除最优:
        else
        {
            pointer = head;
            int stepNumber = 0, sign = 0;
            while(pointer != NULL)
            {
                if(stepNumber != pointer->contemporaryStepDecision)
                {
                    stepNumber = pointer->contemporaryStepDecision;
                    sign = 0;
                    assistant = pointer;
                    while(assistant->contemporaryStepDecision == stepNumber)
                    {
                        if(assistant->b1.blood()<=0 && assistant->b2.blood()<=0)sign = 1;
                        assistant = assistant->next;
                        if(assistant==NULL)break;
                    }
                }
                if(sign==1)
                {
                    deleter = pointer;
                    assistant = pointer->former;
                    pointer = pointer->next;
                    if(pointer!=NULL)pointer->former = assistant;
                    if(assistant!=NULL)assistant->next = pointer;
                    else head = pointer;
                    delete deleter;
                }
                else pointer = pointer->next;
            }
        }
    //列表为空则达到行动的尽头:
        if(head==NULL){optimumDecisionCode = optimum.firstStepDecision; optimumAttackOrder = optimum.attackOrder; goto build;}
    //下一层:
        depth++;
        }
        optimumDecisionCode = optimum.firstStepDecision;
        optimumAttackOrder = optimum.attackOrder;

    build:
        action1 = (optimumDecisionCode%25==0)? (optimumDecisionCode/25) : (int)(optimumDecisionCode/25+1); action2 = (optimumDecisionCode%25==0)? 25 : (optimumDecisionCode%25);
        move1 = (action1%5==0)? (action1/5) : (int)(action1/5+1); attack1 = (action1%5==0)? 5 : (action1%5);
        move2 = (action2%5==0)? (action2/5) : (int)(action2/5+1); attack2 = (action2%5==0)? 5 : (action2%5);
        finalDecision FD(b3,b4,b1,b2,move1,attack1,move2,attack2,optimumAttackOrder);
        return FD;
    }

    bool verify(const finalDecision& d)//用以在战斗中检验用户的输入
    {
        monInBattle b1 = d.b1, b2 = d.b2, b3 = d.b3, b4 = d.b4;
        int x1 = b1.coordinate[0], y1 = b1.coordinate[1], x2 = b2.coordinate[0], y2 = b2.coordinate[1];
        int x3 = b3.coordinate[0], y3 = b3.coordinate[1], x4 = b4.coordinate[0], y4 = b4.coordinate[1];

        if(b1.survive()){
        if(d.move1==2 && x1<=1)return false;
        else if(d.move1==3 && x1>=SIZE)return false;
        else if(d.move1==4 && y1>=SIZE)return false;
        else if(d.move1==5 && y1<=1)return false;
        }else if(d.move1!=1)return false;
        if(b2.survive()){
        if(d.move2==2 && x2<=1)return false;
        else if(d.move2==3 && x2>=SIZE)return false;
        else if(d.move2==4 && y2>=SIZE)return false;
        else if(d.move2==5 && y2<=1)return false;
        }else if(d.move2!=1)return false;
        if(d.move1==2)x1-=1;
        else if(d.move1==3)x1+=1;
        else if(d.move1==4)y1+=1;
        else if(d.move1==5)y1-=1;
        if(d.move2==2)x2-=1;
        else if(d.move2==3)x2+=1;
        else if(d.move2==4)y2+=1;
        else if(d.move2==5)y2-=1;
        if((x1==x2&&y1==y2&&b1.survive()&&b2.survive())||(x1==x3&&y1==y3&&b1.survive()&&b3.survive())||(x1==x4&&y1==y4&&b1.survive()&&b4.survive())||
            (x2==x4&&y2==y4&&b2.survive()&&b4.survive())||(x2==x3&&y2==y3&&b2.survive()&&b3.survive())||(x3==x4&&y3==y4&&b3.survive()&&b4.survive()))return false;
        if(d.attackOrder==0 && b2.survive() && x1==b2.coordinate[0] && y1==b2.coordinate[1])return false;
        else if(d.attackOrder==1 && b1.survive() && x2==b1.coordinate[0] && y2==b1.coordinate[1])return false;
        if(b1.survive()&&b2.survive()&&(x1==b2.coordinate[0]&&y1==b2.coordinate[1])&&(x2==b1.coordinate[0]&&y2==b1.coordinate[1]))return false;
    //判断能不能出击:
        if(b1.survive()){
        if(d.attack1==2||d.attack1==3){if(b3.survive()){if(b1.power()<b1.avePowerConsumption(d.attack1-1))return false;}else return false;}
        else if(d.attack1==4||d.attack1==5){if(b4.survive()){if(b1.power()<b1.avePowerConsumption(d.attack1-3))return false;}else return false;}
        }else if(d.attack1!=1)return false;
        if(b2.survive()){
        if(d.attack2==2||d.attack2==3){if(b3.survive()){if(b2.power()<b2.avePowerConsumption(d.attack2-1))return false;}else return false;}
        else if(d.attack2==4||d.attack2==5){if(b4.survive()){if(b2.power()<b2.avePowerConsumption(d.attack2-3))return false;}else return false;}
        }else if(d.attack2!=1)return false;

        monInBattle m1, m2;
        double di;
        if(d.attack1==2||d.attack1==3)
        {
            di = sqrt(pow((double)(x1-x3),2)+pow((double)(y1-y3),2));
            if(di > b1.distance(d.attack1-1))return false;
        }
        if(d.attack1==4||d.attack1==5)
        {
            di = sqrt(pow((double)(x1-x4),2)+pow((double)(y1-y4),2));
            if(di > b1.distance(d.attack1-3))return false;
        }
        if(d.attack2==2||d.attack2==3)
        {
            di = sqrt(pow((double)(x2-x3),2)+pow((double)(y2-y3),2));
            if(di > b2.distance(d.attack2-1))return false;
        }
        if(d.attack2==4||d.attack2==5)
        {
            di = sqrt(pow((double)(x2-x4),2)+pow((double)(y2-y4),2));
            if(di > b2.distance(d.attack2-3))return false;
        }

        return true;
    }
