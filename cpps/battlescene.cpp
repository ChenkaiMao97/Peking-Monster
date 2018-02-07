#include"battlescene.h"
#include"square.h"
#include"myview.h"
#include"button.h"
#include"monster.h"
#include"AIDecision.h"
#include<QCoreApplication>
#include<QBrush>
#include<QDebug>
#include<QColor>
#include<cmath>
#include<QTime>
#include<QCoreApplication>

#define INITIALX 205
#define INITIALY 65
#define STEP 78

extern Myview* view;

BattleScene::BattleScene(studentData& student)
{
  BS_timer = new Mytimer();
  setBackgroundBrush(QBrush(QImage(":/images/images/BS_bg1.jpg")));
  setSceneRect(0,0,800,600);
  drawPanel();

for(size_t i=0,n=view->view_hero->size();i<n;i++)
{
    mon m=*view->view_hero->Mon(i+1);
    BS_monIB_PL[i] = transMon(m);
    BS_monIC_PL[i] = BS_monIB_PL[i].mon_MonsterIcon;
    addItem(BS_monIC_PL[i]);
    BS_monIC_PL[i]->setPos(30+(i%2)*80,75+i*60);
    BS_monIC_PL[i]->Icon_Monster->Monster_HPBar->setfullValue(BS_monIB_PL[i].fullBlood());
    BS_monIC_PL[i]->Icon_Monster->Monster_HPBar->setvalue(BS_monIB_PL[i].blood());
    BS_monIC_PL[i]->Icon_Monster->Monster_HPBar->displayValue();
    BS_monIC_PL[i]->Icon_Monster->Monster_MPBar->setfullValue(BS_monIB_PL[i].fullPower());
    BS_monIC_PL[i]->Icon_Monster->Monster_MPBar->setvalue(BS_monIB_PL[i].power());
    BS_monIC_PL[i]->Icon_Monster->Monster_MPBar->displayValue();
    BS_monIC_PL[i]->setIconColor();
    BS_monIC_PL[i]->Icon_Tag = new Tag(&BS_monIB_PL[i]);

}
for(size_t n=view->view_hero->size(),i=n;i<6;i++)
{
  BS_monIB_PL[i] = monInBattle();
  BS_monIC_PL[i] = NULL;
}

for(int i=0;i<2;i++)
{
    BS_monIB_AI[i]=transMon(*student.Mon(i+1));
    BS_monIC_AI[i]=student.Mon(i+1)->mon_MonsterIcon;
    BS_monIC_AI[i]->Icon_Tag = new Tag(&BS_monIB_AI[i]);

    BS_monIC_AI[i]->Icon_Monster->Monster_HPBar->setfullValue(BS_monIB_AI[i].fullBlood());
    BS_monIC_AI[i]->Icon_Monster->Monster_HPBar->setvalue(BS_monIB_AI[i].blood());
    BS_monIC_AI[i]->Icon_Monster->Monster_HPBar->displayValue();
    BS_monIC_AI[i]->Icon_Monster->Monster_MPBar->setfullValue(BS_monIB_AI[i].fullPower());
    BS_monIC_AI[i]->Icon_Monster->Monster_MPBar->setvalue(BS_monIB_AI[i].power());
    BS_monIC_AI[i]->Icon_Monster->Monster_MPBar->displayValue();
}
for(size_t n=2,i=n;i<6;i++)
{
  BS_monIB_AI[i] = monInBattle();
  BS_monIC_AI[i] = NULL;
}
    BS_monIB_onStage[2]=&BS_monIB_AI[0]; BS_monIB_onStage[2]->setCoordinate(SIZE,SIZE);
    BS_monIC_AI[0]->Icon_Monster->setMIBnumber(2);
    BS_monIB_onStage[3]=&BS_monIB_AI[1]; BS_monIB_onStage[3]->setCoordinate(1,SIZE);
    BS_monIC_AI[1]->Icon_Monster->setMIBnumber(3);

    addItem(BS_monIC_AI[0]);BS_monIC_AI[0]->setPos(600+80,75);
    addItem(BS_monIC_AI[1]);BS_monIC_AI[1]->setPos(600,135);
    addItem(BS_monIC_AI[0]->Icon_Monster);BS_monIC_AI[0]->Icon_Monster->setPos(INITIALX+4*STEP,INITIALY+4*STEP);BS_monIC_AI[0]->Icon_Monster->setHasBeenAdded(true);
    addItem(BS_monIC_AI[1]->Icon_Monster);BS_monIC_AI[1]->Icon_Monster->setPos(INITIALX+4*STEP,INITIALY);BS_monIC_AI[1]->Icon_Monster->setHasBeenAdded(true);

  BS_dialogue= new Dialogue(this);
  addItem(BS_dialogue);
  BS_dialogue->setPos(10,490);

//先设好Button\text：
  BS_Text = new MyTextItem();
  BS_dialogue->Dialogue_TextItem=BS_Text;
  button_play = new Button(100,40,"PLAY",BS_dialogue);
  button_quit = new Button(100,40,"QUIT",BS_dialogue);
  connect(button_play,SIGNAL(clicked()),view,SLOT(setInitial()));
  connect(button_quit,SIGNAL(clicked()),view,SLOT(setMainscene()));

  button_move = new Button(100,40,"Move",BS_dialogue);
  button_change = new Button(100,40,"Change",BS_dialogue);
  button_bag = new Button(100,40,"Bag",BS_dialogue);
  button_skill = new Button(100,40,"Skill",BS_dialogue);
  button_pass = new Button(100,40,"Pass",BS_dialogue);
  button_escape = new Button(100,40,"Escape",BS_dialogue);
  button_back = new Button(100,40,"Back",BS_dialogue);

 // connect(button_bag,SIGNAL(clicked()),view,SLOT(!!!!!));
  connect(button_move,SIGNAL(clicked()),this,SLOT(MonBeing_setChangeColor()));
 // connect(button_change,SIGNAL(clicked()),view,SLOT(!!!!!));
  connect(button_skill,SIGNAL(clicked()),this,SLOT(showSkillButton()));
  connect(button_pass,SIGNAL(clicked()),this,SLOT(passMon()));
  connect(button_escape,SIGNAL(clicked()),this,SLOT(escape()));
  connect(button_back,SIGNAL(clicked()),this,SLOT(setButton_MoveSkill()));

  button_skillname[0] = new SkillButton(100,40," ",BS_dialogue);button_skillname[0]->setSkillNumber(1);
  button_skillname[1] = new SkillButton(100,40," ",BS_dialogue);button_skillname[1]->setSkillNumber(2);
  connect(button_skillname[0],SIGNAL(clicked()),this,SLOT(useskill1()));
  connect(button_skillname[0],SIGNAL(skillNumber(int)),this,SLOT(skillRange(int)));
  connect(button_skillname[0],SIGNAL(ToBS_skillSquareBack()),this,SLOT(skill_SquareBTN()));
  connect(button_skillname[1],SIGNAL(clicked()),this,SLOT(useskill2()));
  connect(button_skillname[1],SIGNAL(skillNumber(int)),this,SLOT(skillRange(int)));
  connect(button_skillname[1],SIGNAL(ToBS_skillSquareBack()),this,SLOT(skill_SquareBTN()));

//开始初始化
  setButton_PlayQuit();

}

BattleScene::BattleScene(characterData &character)
{

      BS_timer = new Mytimer();
      setBackgroundBrush(QBrush(QImage(":/images/images/BS_bg1.jpg")));
      setSceneRect(0,0,800,600);
      drawPanel();

    for(size_t i=0,n=view->view_hero->size();i<n;i++)
    {
        BS_monIB_PL[i] = transMon(*view->view_hero->Mon(i+1));
        BS_monIC_PL[i] = view->view_hero->Mon(i+1)->mon_MonsterIcon;
        addItem(BS_monIC_PL[i]);
        BS_monIC_PL[i]->setPos(30+(i%2)*80,75+i*60);
        BS_monIC_PL[i]->Icon_Monster->Monster_HPBar->setfullValue(BS_monIB_PL[i].fullBlood());
        BS_monIC_PL[i]->Icon_Monster->Monster_HPBar->setvalue(BS_monIB_PL[i].blood());
        BS_monIC_PL[i]->Icon_Monster->Monster_HPBar->displayValue();
        BS_monIC_PL[i]->Icon_Monster->Monster_MPBar->setfullValue(BS_monIB_PL[i].fullPower());
        BS_monIC_PL[i]->Icon_Monster->Monster_MPBar->setvalue(BS_monIB_PL[i].power());
        BS_monIC_PL[i]->Icon_Monster->Monster_MPBar->displayValue();
        BS_monIC_PL[i]->setIconColor();
        BS_monIC_PL[i]->Icon_Tag = new Tag(&BS_monIB_PL[i]);

    }
    for(size_t n=view->view_hero->size(),i=n;i<6;i++)
    {
      BS_monIB_PL[i] = monInBattle();
      BS_monIC_PL[i] = NULL;
    }

    for(int i=0,n=character.size();i<n;i++)
    {
        BS_monIB_AI[i]=transMon(*character.Mon(i+1));
        BS_monIC_AI[i]=character.Mon(i+1)->mon_MonsterIcon;
        BS_monIC_AI[i]->Icon_Tag = new Tag(&BS_monIB_AI[i]);

        BS_monIC_AI[i]->Icon_Monster->Monster_HPBar->setfullValue(BS_monIB_AI[i].fullBlood());
        BS_monIC_AI[i]->Icon_Monster->Monster_HPBar->setvalue(BS_monIB_AI[i].blood());
        BS_monIC_AI[i]->Icon_Monster->Monster_HPBar->displayValue();
        BS_monIC_AI[i]->Icon_Monster->Monster_MPBar->setfullValue(BS_monIB_AI[i].fullPower());
        BS_monIC_AI[i]->Icon_Monster->Monster_MPBar->setvalue(BS_monIB_AI[i].power());
        BS_monIC_AI[i]->Icon_Monster->Monster_MPBar->displayValue();
        addItem(BS_monIC_AI[i]);BS_monIC_AI[i]->setPos(600+((i+1)%2)*80,75+i*60);
    }

        BS_monIB_onStage[2]=&BS_monIB_AI[0]; BS_monIB_onStage[2]->setCoordinate(SIZE,SIZE);
        BS_monIC_AI[0]->Icon_Monster->setMIBnumber(2);
        BS_monIB_onStage[3]=&BS_monIB_AI[1]; BS_monIB_onStage[3]->setCoordinate(1,SIZE);
        BS_monIC_AI[1]->Icon_Monster->setMIBnumber(3);


        addItem(BS_monIC_AI[0]->Icon_Monster);BS_monIC_AI[0]->Icon_Monster->setPos(INITIALX+4*STEP,INITIALY+4*STEP);BS_monIC_AI[0]->Icon_Monster->setHasBeenAdded(true);
        addItem(BS_monIC_AI[1]->Icon_Monster);BS_monIC_AI[1]->Icon_Monster->setPos(INITIALX+4*STEP,INITIALY);BS_monIC_AI[1]->Icon_Monster->setHasBeenAdded(true);

      BS_dialogue= new Dialogue(this);
      addItem(BS_dialogue);
      BS_dialogue->setPos(10,490);

    //先设好Button\text：
      BS_Text = new MyTextItem();
      BS_dialogue->Dialogue_TextItem=BS_Text;
      button_play = new Button(100,40,"PLAY",BS_dialogue);
      button_quit = new Button(100,40,"QUIT",BS_dialogue);
      connect(button_play,SIGNAL(clicked()),view,SLOT(setInitial()));
      connect(button_quit,SIGNAL(clicked()),view,SLOT(setMainscene()));

      button_move = new Button(100,40,"Move",BS_dialogue);
      button_change = new Button(100,40,"Change",BS_dialogue);
      button_bag = new Button(100,40,"Bag",BS_dialogue);
      button_skill = new Button(100,40,"Skill",BS_dialogue);
      button_pass = new Button(100,40,"Pass",BS_dialogue);
      button_escape = new Button(100,40,"Escape",BS_dialogue);
      button_back = new Button(100,40,"Back",BS_dialogue);

     // connect(button_bag,SIGNAL(clicked()),view,SLOT(!!!!!));
      connect(button_move,SIGNAL(clicked()),this,SLOT(MonBeing_setChangeColor()));
     // connect(button_change,SIGNAL(clicked()),view,SLOT(!!!!!));
      connect(button_skill,SIGNAL(clicked()),this,SLOT(showSkillButton()));
      connect(button_pass,SIGNAL(clicked()),this,SLOT(passMon()));
      connect(button_escape,SIGNAL(clicked()),this,SLOT(escape()));
      connect(button_back,SIGNAL(clicked()),this,SLOT(setButton_MoveSkill()));

      button_skillname[0] = new SkillButton(100,40," ",BS_dialogue);button_skillname[0]->setSkillNumber(1);
      button_skillname[1] = new SkillButton(100,40," ",BS_dialogue);button_skillname[1]->setSkillNumber(2);
      connect(button_skillname[0],SIGNAL(clicked()),this,SLOT(useskill1()));
      connect(button_skillname[0],SIGNAL(skillNumber(int)),this,SLOT(skillRange(int)));
      connect(button_skillname[0],SIGNAL(ToBS_skillSquareBack()),this,SLOT(skill_SquareBTN()));
      connect(button_skillname[1],SIGNAL(clicked()),this,SLOT(useskill2()));
      connect(button_skillname[1],SIGNAL(skillNumber(int)),this,SLOT(skillRange(int)));
      connect(button_skillname[1],SIGNAL(ToBS_skillSquareBack()),this,SLOT(skill_SquareBTN()));

    //开始初始化
      setButton_PlayQuit();

}

void BattleScene::drawPanel()
{qDebug()<<"draw panel";

    for(size_t i=0,n=5;i<n;i++)
      {for(size_t j=0,n=5;j<n;j++)
        {
          Square *square = new Square();
          addItem(square);
          square->setPos(INITIALX+i*STEP,INITIALY+j*STEP);       
        }
    }
}

void BattleScene::clearChangeColorState()
{
    for(size_t i=0;i<5;i++)
    {
      for(size_t j=0;j<5;j++)
      {
        dynamic_cast<Square*>(itemAt(INITIALX+i*STEP,INITIALY+j*STEP,QTransform()))->backToNormal();
        dynamic_cast<Square*>(itemAt(INITIALX+i*STEP,INITIALY+j*STEP,QTransform()))->setS_shining(false);
      }
    }
}

void BattleScene::adMon_OnStage()
{
    mon_OnStage += 1;
}

void BattleScene::deMon_OnStage()
{
    mon_OnStage -= 1;
}

int BattleScene::getMon_OnStage()
{
    return mon_OnStage;
}

void BattleScene::setMonsterChangeColor(bool b)
{if(b)
   {
    BS_monIB_onStage[0]->mon_MonsterIcon->Icon_Monster->changeColorMode();
    BS_monIB_onStage[1]->mon_MonsterIcon->Icon_Monster->changeColorMode();
   }
 else
    {
        BS_monIB_onStage[0]->mon_MonsterIcon->Icon_Monster->clearChangeColorMode();
        BS_monIB_onStage[1]->mon_MonsterIcon->Icon_Monster->clearChangeColorMode();
    }
}

void BattleScene::showSkillButton()
{
    button_skillname[0]->button_Text->setPlainText(BS_monIB_PL[mon_BeingSelected->monNumber-1].skillName(1));
    button_skillname[1]->button_Text->setPlainText(BS_monIB_PL[mon_BeingSelected->monNumber-1].skillName(2));
    button_skillname[0]->placetext();
    button_skillname[1]->placetext();
    setButton_Skillname();
}

void BattleScene::useskill1()
{
   qDebug()<<"skill1";
   bool canskill=0;
   Square* S2=dynamic_cast<Square*>(itemAt(BS_monIB_onStage[2]->mon_MonsterIcon->Icon_Monster->pos(),QTransform()));
   Square* S3=dynamic_cast<Square*>(itemAt(BS_monIB_onStage[3]->mon_MonsterIcon->Icon_Monster->pos(),QTransform()));
   for(size_t i=0,n=skill_Square.size();i<n;i++)
   {
    if(S2==skill_Square[i])
    {
        BS_monIB_onStage[2]->mon_MonsterIcon->Icon_Monster->changeRedMode();
        canskill=true;
    }
    else{continue;}
   }
   for(size_t i=0,n=skill_Square.size();i<n;i++)
   {
    if(S3==skill_Square[i])
    {
        BS_monIB_onStage[3]->mon_MonsterIcon->Icon_Monster->changeRedMode();
        canskill=true;
    }
    else{continue;}
   }
   if(!canskill){qDebug()<<"You can't use skill1";return;}
   else
   {
     setOpInt_Number(1);
     setStage_ButtonOnly(false);
     setStage_ChooseSkillMon(true);
   }

}

void BattleScene::useskill2()
{
    qDebug()<<"skill2";
    bool canskill=0;
    Square* S2=dynamic_cast<Square*>(itemAt(BS_monIB_onStage[2]->mon_MonsterIcon->Icon_Monster->pos(),QTransform()));
    Square* S3=dynamic_cast<Square*>(itemAt(BS_monIB_onStage[3]->mon_MonsterIcon->Icon_Monster->pos(),QTransform()));
    for(size_t i=0,n=skill_Square.size();i<n;i++)
    {
     if(S2==skill_Square[i])
     {
         BS_monIB_onStage[2]->mon_MonsterIcon->Icon_Monster->changeRedMode();
         canskill=true;
     }
     else{continue;}
    }
    for(size_t i=0,n=skill_Square.size();i<n;i++)
    {
     if(S3==skill_Square[i])
     {
         BS_monIB_onStage[3]->mon_MonsterIcon->Icon_Monster->changeRedMode();
         canskill=true;
     }
     else{continue;}
    }
    if(!canskill){qDebug()<<"You can't use skill2";return;}
    else
    {
      setOpInt_Number(2);
      setStage_ButtonOnly(false);
      setStage_ChooseSkillMon(true);
    }
}

void BattleScene::passMon()
{
    setStage_ButtonOnly(false);
    qDebug()<<"passMon";
    mon_BeingSelected->setM_alldone(true);
    //monoperation
    setOpInt1_Number(mon_BeingSelected->getMIBnumber()+1);
    monOperation(BS_Situation,getOpInt1_Number(),getOpInt2_Move(),getOpInt3_Attack());qDebug()<<getOpInt1_Number()<<getOpInt2_Move()<<getOpInt3_Attack();
    displayChange();

    mon_BeingSelected->clearChangeColorMode();
    int i = (mon_BeingSelected->getMIBnumber()+1)%2;
    setMon_BeingSelected(BS_monIB_onStage[i]->mon_MonsterIcon->Icon_Monster);
    setOpInt_Number(0);setOpInt1_Number(i+1);setOpInt2_Move(1);setOpInt3_Attack(1);
    if(mon_BeingSelected->getM_alldone())
    {
        //Turn 初始化
        removeAll();
        setMon_BeingSelected(NULL);
        setMon_BeingAttack(NULL);

        BS_monIB_onStage[0]->mon_MonsterIcon->Icon_Monster->setM_moved(false);
        BS_monIB_onStage[0]->mon_MonsterIcon->Icon_Monster->setM_alldone(false);
        BS_monIB_onStage[1]->mon_MonsterIcon->Icon_Monster->setM_moved(false);
        BS_monIB_onStage[1]->mon_MonsterIcon->Icon_Monster->setM_alldone(false);
        setOpInt_Number(0);
        setOpInt1_Number(0);
        setOpInt2_Move(1);
        setOpInt3_Attack(1);
        qDebug()<<"Your turn over, AI turn begins";
        //AI turn!
        BS_Decision = finalDecision(AIDecision(BS_Situation));
        setBS_Message("AI Turn Begins.");
        anotherTurn();
    }
    else
    {
        mon_BeingSelected->changeColorMode();
        setStage_ButtonOnly(true);
        setButton_MoveSkill();
    }
}

void BattleScene::escape()
{
  view->setMainscene();
//惩罚
}

void BattleScene::setBS_Message(QString message)
{
    removeAll();
    BS_Text->setPlainText(message);
    BS_dialogue->setTextItem(BS_Text);
    addItem(BS_dialogue->Dialogue_TextItem);
    BS_dialogue->Dialogue_TextItem->add();
}

void BattleScene::skillRange(int n)
{

    skill_Square.clear();qDebug()<<"square cleared";
    if(BS_monIB_onStage[mon_BeingSelected->getMIBnumber()]->avePowerConsumption(n)>BS_monIB_onStage[mon_BeingSelected->getMIBnumber()]->power())
    {
        button_skillname[n-1]->setRed();
        return;
    }
    double S_dis = BS_monIB_onStage[mon_BeingSelected->getMIBnumber()]->distance(n);
    int centerx = mon_BeingSelected->x();
    int centery = mon_BeingSelected->y();
    for(size_t i=0;i<5;i++)
    {
      for(size_t j=0;j<5;j++)
      {
          bool b1=distance(centerx,centery,INITIALX+i*STEP,INITIALY+j*STEP)<=S_dis;
          //加一个b2判断有没有monster
        if(b1)
        {
            dynamic_cast<Square*>(itemAt(INITIALX+i*STEP,INITIALY+j*STEP,QTransform()))->lighter();
            skill_Square.append(dynamic_cast<Square*>(itemAt(INITIALX+i*STEP,INITIALY+j*STEP,QTransform())));
        }
        else{continue;}
      }
    }

}

void BattleScene::skill_SquareBTN()
{
    for(size_t i=0,n=skill_Square.size();i<n;i++)
    {
        skill_Square[i]->setSquareColor();
    }
}

Monster *BattleScene::getMon_BeingAttack() const
{
    return mon_BeingAttack;
}

void BattleScene::setMon_BeingAttack(Monster *value)
{
    mon_BeingAttack = value;
}

int BattleScene::getOpInt3_Attack() const
{
    return opInt3_Attack;
}

void BattleScene::setOpInt3_Attack(int value)
{
    opInt3_Attack = value;
}

int BattleScene::getOpInt_Number() const
{
    return opInt_Number;
}

void BattleScene::setOpInt_Number(int value)
{
    opInt_Number = value;
}

int BattleScene::getOpInt2_Move() const
{
    return opInt2_Move;
}

void BattleScene::setOpInt2_Move(int value)
{
    opInt2_Move = value;
}

int BattleScene::getOpInt1_Number() const
{
    return opInt1_Number;
}

void BattleScene::setOpInt1_Number(int value)
{
    opInt1_Number = value;
}

bool BattleScene::getStage_ChooseSkillMon() const
{
    return stage_ChooseSkillMon;
}

void BattleScene::setStage_ChooseSkillMon(bool value)
{
    stage_ChooseSkillMon = value;
}

bool BattleScene::getStage_ChooseSkill() const
{
    return stage_ChooseSkill;
}

void BattleScene::setStage_ChooseSkill(bool value)
{
    stage_ChooseSkill = value;
}

void BattleScene::anotherTurn()
{
 if(BS_Decision.attackOrder==0)
 {
  setStage_ButtonOnly(false);
  monOperation(BS_Situation,3,BS_Decision.move1,BS_Decision.attack1);qDebug()<<3<<BS_Decision.move1<<BS_Decision.attack1;
  animate_move(BS_monIB_onStage[2]->mon_MonsterIcon->Icon_Monster,BS_Decision.move1,STEP,1300,13);qDebug()<<"3 moveAnimate";
  sleep(2000);
  displayChange();
  sleep(1000);
  monOperation(BS_Situation,4,BS_Decision.move2,BS_Decision.attack2);qDebug()<<4<<BS_Decision.move2<<BS_Decision.attack2;
  animate_move(BS_monIB_onStage[3]->mon_MonsterIcon->Icon_Monster,BS_Decision.move2,STEP,1300,13);qDebug()<<"4 moveAnimate";
  sleep(2000);
  displayChange();
  sleep(1000);
  BS_monIB_onStage[0]->mon_MonsterIcon->Icon_Monster->changeColorMode();
  BS_monIB_onStage[1]->mon_MonsterIcon->Icon_Monster->changeColorMode();
  setStage_ChooseMon(true);
  setBS_Message("Please Choose a Monster.");

 }

 else
 {
     monOperation(BS_Situation,4,BS_Decision.move1,BS_Decision.attack2);qDebug()<<4<<BS_Decision.move2<<BS_Decision.attack2;
     animate_move(BS_monIB_onStage[3]->mon_MonsterIcon->Icon_Monster,BS_Decision.move2,STEP,1300,13);qDebug()<<"4 moveAnimate";
     displayChange();
     sleep(2000);
     monOperation(BS_Situation,3,BS_Decision.move1,BS_Decision.attack1);qDebug()<<3<<BS_Decision.move1<<BS_Decision.attack1;
     animate_move(BS_monIB_onStage[2]->mon_MonsterIcon->Icon_Monster,BS_Decision.move1,STEP,1300,13);qDebug()<<"3 moveAnimate";
     displayChange();
     setStage_ButtonOnly(false);
     sleep(2000);
     BS_monIB_onStage[0]->mon_MonsterIcon->Icon_Monster->changeColorMode();
     BS_monIB_onStage[1]->mon_MonsterIcon->Icon_Monster->changeColorMode();
     setStage_ChooseMon(true);
 }
removeAll();
return;
}

void BattleScene::removeAll()
{
    removeMessage();
    if(button_play->getHasBeenAdded())  { removeItem(button_play);  button_play->remove();}
    if(button_quit->getHasBeenAdded())  { removeItem(button_quit);  button_quit->remove();}
    if(button_move->getHasBeenAdded())  { removeItem(button_move);  button_move->remove();}
    if(button_change->getHasBeenAdded()){ removeItem(button_change);button_change->remove();}
    if(button_skill->getHasBeenAdded()) { removeItem(button_skill); button_skill->remove();}
    if(button_pass->getHasBeenAdded())  { removeItem(button_pass);  button_pass->remove();}
    if(button_escape->getHasBeenAdded()){ removeItem(button_escape);button_escape->remove();}
    if(button_bag->getHasBeenAdded())   { removeItem(button_bag);   button_bag->remove();}
    if(button_skillname[0]->getHasBeenAdded()){  removeItem(button_skillname[0]); button_skillname[0]->remove();}
    if(button_skillname[1]->getHasBeenAdded()){  removeItem(button_skillname[1]);     button_skillname[1]->remove();}
    if(button_back->getHasBeenAdded()){  removeItem(button_back);     button_back->remove();}
}

double BattleScene::distance(int x1, int y1, int x2, int y2)
{
    double X1=static_cast<double>(x1),Y1=static_cast<double>(y1),X2=static_cast<double>(x2),Y2=static_cast<double>(y2);
    return sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2))/static_cast<double>(STEP);
}

void BattleScene::removeMessage()
{
    if(BS_Text->getHasBeenAdded()){removeItem(BS_Text);BS_Text->remove();}
}

void BattleScene::judgeOver()
{

    if(BS_monIB_onStage[2]->survive()==false&&BS_monIB_onStage[3]->survive()==false)
    {

        for(size_t i=0;i<2;i++)
        {
            int a = BS_monIB_onStage[i]->fullExperienceValue()/BS_monIB_onStage[i]->level()*2;
            int b = 2*BS_monIB_onStage[2]->level()+2*BS_monIB_onStage[3]->level()-BS_monIB_onStage[i]->level();
            b = b<1?1:b; int c = rand()%2;
            if(c)c = 1;else c = -1;
            b = (int)(a*b*(1+c*(rand()%50)/100));
            BS_monIB_onStage[i]->adExperienceValue(b);
        }
        for(size_t i=0,n=view->view_hero->size();i<n;i++)
        {
            BS_monIB_PL[i].adPower(BS_monIB_PL[i].fullPower());
            BS_monIB_PL[i].mon_MonsterIcon->Icon_Monster->setInitial();
            BS_monIB_PL[i].mon_MonsterIcon->Icon_Monster->Monster_MPBar->displayValue();


            *(view->view_hero->Mon(i+1)) = mon(BS_monIB_PL[i]);
            setBS_Message("YOU WIN");
            sleep(5000);
        }
        view->setMainscene();
    }

    if(BS_monIB_onStage[0]->survive()==false&&BS_monIB_onStage[1]->survive()==false)
    {
        for(size_t i=0,n=view->view_hero->size();i<n;i++)
        {
            BS_monIB_PL[i].adPower(BS_monIB_PL[i].fullPower());
            BS_monIB_PL[i].adBlood(BS_monIB_PL[i].fullBlood());
            BS_monIB_PL[i].mon_MonsterIcon->Icon_Monster->setInitial();
            BS_monIB_PL[i].mon_MonsterIcon->Icon_Monster->Monster_MPBar->displayValue();
            *(view->view_hero->Mon(i+1)) = mon(BS_monIB_PL[i]);
            //重生地点、金钱减半、重生事件、GPA惩罚
            setBS_Message("YOU LOSE");
            sleep(5000);
        }
        view->setMainscene();
    }
}

void BattleScene::sleep(int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {QCoreApplication::processEvents(QEventLoop::AllEvents,100);}
    return;
}

void BattleScene::displayChange()
{
    for(size_t i=0,n=4;i<n;i++)
    {
        BS_monIB_onStage[i]->mon_MonsterIcon->Icon_Monster->Monster_HPBar->animateChange(BS_monIB_onStage[i]->mon_MonsterIcon->Icon_Monster->Monster_HPBar->value,BS_monIB_onStage[i]->blood());
        BS_monIB_onStage[i]->mon_MonsterIcon->Icon_Monster->Monster_MPBar->animateChange(BS_monIB_onStage[i]->mon_MonsterIcon->Icon_Monster->Monster_MPBar->value,BS_monIB_onStage[i]->power());

        if(BS_monIB_onStage[i]->survive()==false)
        {sleep(1000);
            BS_monIB_onStage[i]->mon_MonsterIcon->setIconColor();
            animate_kill(BS_monIB_onStage[i]->mon_MonsterIcon->Icon_Monster);
        }
    }
    judgeOver();
    return;

}

void BattleScene::animate_kill(Monster *MST_ToKill)
{
    MST_ToKill->setM_alldone(true);
    if(!MST_ToKill->getHasBeenAdded()){return;}
    else
    {
        removeItem(MST_ToKill);
        MST_ToKill->setHasBeenAdded(false);return;
    }
}

void BattleScene::animate_move(QGraphicsItem *item, char direction, int distance, int wholetime, int times)
{

    if(direction=='a'){return;}
    BSA_item=item;BSA_direction=direction;BSA_distance=distance;BSA_wholetime=wholetime;BSA_times=times;

    BS_timer->settimes(0);
    BS_timer->setInterval(wholetime/times);
    BS_timer->start();
    connect(BS_timer,SIGNAL(timeout()),this,SLOT(setAnimate_move()));

}

void BattleScene::animate_move(QGraphicsItem *item, int direction, int distance, int wholetime, int times)
{
    BSA_item=item;BSA_distance=distance;BSA_wholetime=wholetime;BSA_times=times;
    switch(direction)
    {
    case 1:BSA_direction='a';break;
    case 2:BSA_direction='u';break;
    case 3:BSA_direction='d';break;
    case 4:BSA_direction='r';break;
    case 5:BSA_direction='l';break;
    }
    if(BSA_direction=='a'){return;}
    qDebug()<<BSA_direction;
    BS_timer->settimes(0);
    BS_timer->setInterval(wholetime/times);
    BS_timer->start();
    connect(BS_timer,SIGNAL(timeout()),this,SLOT(setAnimate_move()));

}

void BattleScene::setButton_PlayQuit()
{
    qDebug()<<"Initial buttons";
    removeAll();
    BS_dialogue->setButton(button_play,200,32); button_play->setNormalColor(); button_play->add();
    BS_dialogue->setButton(button_quit,500,32); button_quit->setNormalColor(); button_quit->add();
}

void BattleScene::setButton_MoveSkill()
{
    removeAll();
    BS_dialogue->setButton(button_move,100,10);   button_move->add();  button_move->setNormalColor();
    BS_dialogue->setButton(button_change,100,50); button_change->add();button_change->setNormalColor();
    BS_dialogue->setButton(button_skill,350,10);  button_skill->add(); button_skill->setNormalColor();
    BS_dialogue->setButton(button_bag,350,50);    button_bag->add();   button_bag->setNormalColor();
    BS_dialogue->setButton(button_pass,600,10);   button_pass->add();  button_pass->setNormalColor();
    BS_dialogue->setButton(button_escape,600,50); button_escape->add();button_escape->setNormalColor();
}

void BattleScene::setAnimate_move()
{
    BS_timer->addtimes(BSA_times+1);
    if(BS_timer->gettimes()==0){BS_timer->stop(); BS_timer->disconnect(); return;}
    int movelength = BSA_distance/BSA_times;
    switch(BSA_direction)
    {
    case 'l':BSA_item->setPos(BSA_item->x()-movelength,BSA_item->y());break;
    case 'r':BSA_item->setPos(BSA_item->x()+movelength,BSA_item->y());break;
    case 'u':BSA_item->setPos(BSA_item->x(),BSA_item->y()-movelength);break;
    case 'd':BSA_item->setPos(BSA_item->x(),BSA_item->y()+movelength);break;
    }
}

void BattleScene::setButton_Skillname()
{
   removeAll();
   BS_dialogue->setButton(button_skillname[0],150,30);button_skillname[0]->add();button_skillname[0]->setNormalColor();
   BS_dialogue->setButton(button_skillname[1],450,30);button_skillname[1]->add();button_skillname[1]->setNormalColor();
   BS_dialogue->setButton(button_back,550,30);button_back->add();button_back->setNormalColor();
}

Monster *BattleScene::getMon_BeingSelected() const
{
    return mon_BeingSelected;
}

void BattleScene::setMon_BeingSelected(Monster *value)
{
    mon_BeingSelected = value;
}

void BattleScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"scenemouse event";
//***********是否对战*******************
if(getStage_ButtonOnly())
  {qDebug()<<"ButtonOnly";
    if(dynamic_cast<Button*>(itemAt(event->scenePos(),QTransform()))||dynamic_cast<QGraphicsTextItem*>(itemAt(event->scenePos(),QTransform())))
       {
        QGraphicsScene::mousePressEvent(event);   //stage 切换写在event函数里面
        return;
       }
    else{return;}
  }
//***********初始化*******************
if(getStage_Initial())
  {qDebug()<<"stage_Initial";
   if(dynamic_cast<MonsterIcon*>(itemAt(event->scenePos(),QTransform())))
   {  MonsterIcon* temporary = dynamic_cast<MonsterIcon*>(itemAt(event->scenePos(),QTransform()));
     if(temporary->getIcon_Shining())
     {
         if(event->button() == Qt::LeftButton)
         {
           temporary->clearChangeColorMode();
           temporary->setIcon_Shining(false);
           addItem(temporary->Icon_Monster);temporary->Icon_Monster->setHasBeenAdded(true);
           qDebug()<<"left";
             switch(getMon_OnStage())
             {
              case 0: qDebug()<<"transmon0";
                 BS_monIB_onStage[0] = &BS_monIB_PL[temporary->monNumber-1];temporary->Icon_Monster->setMIBnumber(0);
                 BS_monIB_onStage[0]->setCoordinate(1,1);
                 break;
              case 1:
                 qDebug()<<"transmon1";BS_monIB_onStage[1] = &BS_monIB_PL[temporary->monNumber-1];temporary->Icon_Monster->setMIBnumber(1);
                 BS_monIB_onStage[1]->setCoordinate(SIZE,1);
                 BS_Situation=initialSituation(BS_monIB_onStage[0],BS_monIB_onStage[1],BS_monIB_onStage[2],BS_monIB_onStage[3]);
                 break;
             }
           temporary->Icon_Monster->setPos(getShining_Place()->pos());
           getShining_Place()->backToNormal();
           adMon_OnStage();
              if(getMon_OnStage()==1)
              {
                 dynamic_cast<Square*>(itemAt(INITIALX,INITIALY+4*STEP,QTransform()))->changeColorMode();
                 setShining_Place(dynamic_cast<Square*>(itemAt(INITIALX,INITIALY+4*STEP,QTransform())));
                 return;
              }
              else if(getMon_OnStage()==2)
              {
               setStage_Initial(false);
               setStage_ChooseMon(true);
               for(size_t i=0,n=view->view_hero->size();i<n;i++)
               {
                   BS_monIC_PL[i]->clearChangeColorMode();
               }

               setMonsterChangeColor(true);
               setBS_Message("Please Choose a Monster");
               return;
              }
          return;
          }
     }
     else {return;}
   }
   else {return;}
  }
//***********选一个怪（场上）*******************
if(getStage_ChooseMon())
{
    if(event->button() == Qt::LeftButton)
    {
      if(dynamic_cast<Monster*>(itemAt(event->scenePos(),QTransform())))
      {
       Monster* m = dynamic_cast<Monster*>(itemAt(event->scenePos(),QTransform()));
         if(m->getM_shining())
         {
           setMon_BeingSelected(m);qDebug()<<"monBeingSelected"<<m->getMIBnumber();
           setMonsterChangeColor(false);
           m->changeColorMode();
           setButton_MoveSkill();
           setStage_ChooseMon(false);
           setStage_ButtonOnly(true);
           return;
         }
         else {return;}
      }
      else{return;}
    }
else {return;}

}

//***********移动*******************
else if(getStage_Move())
 {qDebug()<<"stage_Move";
    if(event->button()==Qt::LeftButton)
    {
       if(dynamic_cast<Square*>(itemAt(event->scenePos(),QTransform())))
       { Square* s = dynamic_cast<Square*>(itemAt(event->scenePos(),QTransform()));
         if(s->getS_shining())
         {
           if(s->x()-getMon_BeingSelected()->x()==0)
           {
               switch(static_cast<int>(s->y()-getMon_BeingSelected()->y()))
               {
               case 0    : setOpInt2_Move(1);break;
               case STEP : setOpInt2_Move(3);break;
               case -STEP: setOpInt2_Move(2);break;
               default: qDebug()<<s->y()-getMon_BeingSelected()->y();
               }
           }
           else{
               switch (static_cast<int>(s->x()-getMon_BeingSelected()->x())) {
               case STEP: setOpInt2_Move(4);break;
               case -STEP:setOpInt2_Move(5);break;
               default: qDebug()<<s->x()-getMon_BeingSelected()->x();
               }
           }

           animate_move(getMon_BeingSelected(),getOpInt2_Move(),STEP,650,13);
           clearChangeColorState();
           sleep(650);
           getMon_BeingSelected()->setM_moved(true);
           setStage_Move(false);
           setStage_ButtonOnly(true);
           return;
         }
         else{return;}
       }
       else{return;}
    }
    else{return;}
  }
//***********选技能*******************

//************选打谁*******************
else if(getStage_ChooseSkillMon())
{
    if(event->button()==Qt::LeftButton)
    {
        if(dynamic_cast<Monster*>(itemAt(event->scenePos(),QTransform())))
        {
            if(dynamic_cast<Monster*>(itemAt(event->scenePos(),QTransform()))->getM_Redding())
            {
               qDebug()<<"select monster redding";
               setMon_BeingAttack(dynamic_cast<Monster*>(itemAt(event->scenePos(),QTransform())));
               if(!mon_BeingSelected->getM_moved())
               {setOpInt2_Move(1);}
               if(getOpInt_Number()==1)
               {
                   if(getMon_BeingAttack()->getMIBnumber()==2)
                   {setOpInt3_Attack(2);}
                   else if(getMon_BeingAttack()->getMIBnumber()==3)
                   {setOpInt3_Attack(4);}
               }
               else if(getOpInt_Number()==2)
               {
                   if(getMon_BeingAttack()->getMIBnumber()==2)
                   {setOpInt3_Attack(3);}
                   else if(getMon_BeingAttack()->getMIBnumber()==3)
                   {setOpInt3_Attack(5);}
               }
               getMon_BeingSelected()->clearChangeColorMode();
               BS_monIB_onStage[2]->mon_MonsterIcon->Icon_Monster->clearChangeRedMode();
               BS_monIB_onStage[3]->mon_MonsterIcon->Icon_Monster->clearChangeRedMode();
               passMon();
               return;
            }
            else{return;}
        }
        else{return;}
    }
    else{return;}
}

}

//***********  *******************
//***********  *******************

void BattleScene::setChangeColorState(int centerx, int centery, double dis)
{
    if(dynamic_cast<Square*>(itemAt(centerx,centery,QTransform()))->getS_shining()) {return;}

   for(size_t i=0;i<5;i++)
   {
     for(size_t j=0;j<5;j++)
     {
         bool b1=distance(centerx,centery,INITIALX+i*STEP,INITIALY+j*STEP)<=dis;
         bool b2=true;
         QList<QGraphicsItem*>CLI=dynamic_cast<Square*>(itemAt(INITIALX+i*STEP,INITIALY+j*STEP,QTransform()))->collidingItems();
         for(size_t i=0,n=CLI.size();i<n;i++)
         {if(dynamic_cast<Monster*>(CLI[i])){b2=false;}}
       if(b1&&b2)
       {
           dynamic_cast<Square*>(itemAt(INITIALX+i*STEP,INITIALY+j*STEP,QTransform()))->changeColorMode();
           dynamic_cast<Square*>(itemAt(INITIALX+i*STEP,INITIALY+j*STEP,QTransform()))->setS_shining(true);
       }
       else{continue;}
     }
   }
    dynamic_cast<Square*>(itemAt(centerx,centery,QTransform()))->changeColorMode();
    dynamic_cast<Square*>(itemAt(centerx,centery,QTransform()))->setS_shining(true);
    return;

}

void BattleScene::MonBeing_setChangeColor()
{
    if(!getMon_BeingSelected()->getM_moved())
    {
     setChangeColorState(getMon_BeingSelected()->x(),getMon_BeingSelected()->y(),1.0);
     getMon_BeingSelected()->setM_moved(true);
     setStage_ButtonOnly(false);
     setStage_Move(true);
     return;
    }
    else {/*play a sound*/return;}
}

Square *BattleScene::getShining_Place() const
{
    return shining_Place;
}

void BattleScene::setShining_Place(Square *value)
{
    shining_Place = value;
}

bool BattleScene::getStage_ChooseMon() const
{
    return stage_ChooseMon;
}

void BattleScene::setStage_ChooseMon(bool value)
{
    stage_ChooseMon = value;
}

bool BattleScene::getStage_ButtonOnly() const
{
    return stage_ButtonOnly;
}

void BattleScene::setStage_ButtonOnly(bool value)
{
    stage_ButtonOnly = value;
}

bool BattleScene::getStage_Over() const
{
    return stage_Over;
}

void BattleScene::setStage_Over(bool value)
{
    stage_Over = value;
}

bool BattleScene::getStage_Skill() const
{
    return stage_Skill;
}

void BattleScene::setStage_Skill(bool value)
{
    stage_Skill = value;
}

bool BattleScene::getStage_Move() const
{
    return stage_Move;
}

void BattleScene::setStage_Move(bool value)
{
    stage_Move = value;
}

bool BattleScene::getStage_AIturn() const
{
    return stage_AIturn;
}

void BattleScene::setStage_AIturn(bool value)
{
    stage_AIturn = value;
}

bool BattleScene::getStage_Initial() const
{
    return stage_Initial;
}

void BattleScene::setStage_Initial(bool value)
{
    stage_Initial = value;
}


