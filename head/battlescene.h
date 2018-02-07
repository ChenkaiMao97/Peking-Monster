#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include<QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsItem>
#include<QObject>
#include<QMutex>
#include"mytextitem.h"
#include"PKUmon.h"
#include"monster.h"
#include"square.h"
#include"button.h"
#include"AIDecision.h"

class BattleScene:public QGraphicsScene
{Q_OBJECT
public:
    BattleScene(){}
    BattleScene(studentData &student);
    BattleScene(characterData& character);
 //public member function
    void drawPanel();
    void clearChangeColorState();
    void adMon_OnStage();
    void deMon_OnStage();
    int  getMon_OnStage();
    void setMonsterChangeColor(bool b);
    void anotherTurn();
    void removeAll();
    double distance(int x1,int y1,int x2,int y2);
    void removeMessage();
    void judgeOver();

    void sleep(int msec);
    void displayChange();
    void animate_kill(Monster* MST_ToKill);
    void animate_move(QGraphicsItem* item,char direction,int distance,int wholetime,int times);
    void animate_move(QGraphicsItem* item, int direction, int distance, int wholetime, int times);
    void animate_move(QGraphicsItem* item, QPointF point, int wholetime, int times);
//各种按钮
      void setButton_PlayQuit(); 
      void setButton_Skillname();

//event
      void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
      void setChangeColorState(int centerx, int centery, double dis);
      void MonBeing_setChangeColor();
      void showSkillButton();
      void useskill1();
      void useskill2();
      void passMon();
      void escape();
      void setBS_Message(QString message);
      void skillRange(int n);
      void skill_SquareBTN();
      void setButton_MoveSkill();
      void setAnimate_move();
//public attributes
public:
      initialSituation BS_Situation;
      finalDecision BS_Decision;
      class Dialogue *BS_dialogue;
      monInBattle BS_monIB_PL[6];
      monInBattle BS_monIB_AI[6];
      monInBattle *BS_monIB_onStage[4]={0};
      MonsterIcon *BS_monIC_PL[6]={0};
      MonsterIcon *BS_monIC_AI[6]={0};
      Button* button_play;
      Button* button_quit;
      Button* button_move;
      Button* button_change;
      Button* button_skill;
      Button* button_pass;
      Button* button_escape;
      Button* button_bag;
      Button* button_back;
      SkillButton* button_skillname[2]={0};
      MyTextItem* BS_Text;
      Mytimer* BS_timer;
      QVector<Square*> skill_Square={0};
//animate datas
      QGraphicsItem* BSA_item=NULL;
      char BSA_direction='a';
      int BSA_distance=0;
      int BSA_wholetime=0;
      int BSA_times=0;
//getters and setters
      bool getStage_Initial() const;
      void setStage_Initial(bool value);
      bool getStage_AIturn() const;
      void setStage_AIturn(bool value);
      bool getStage_Move() const;
      void setStage_Move(bool value);
      bool getStage_Skill() const;
      void setStage_Skill(bool value);
      bool getStage_Over() const;
      void setStage_Over(bool value);
      bool getStage_ButtonOnly() const;
      void setStage_ButtonOnly(bool value);
      bool getStage_ChooseMon() const;
      void setStage_ChooseMon(bool value);
      Monster *getMon_BeingSelected() const;
      void setMon_BeingSelected(Monster *value);
      Monster *getMon_BeingAttack() const;
      void setMon_BeingAttack(Monster *value);
      Square *getShining_Place() const;
      void setShining_Place(Square *value);
      bool getStage_ChooseSkill() const;
      void setStage_ChooseSkill(bool value);
      bool getStage_ChooseSkillMon() const;
      void setStage_ChooseSkillMon(bool value);
      int getOpInt1_Number() const;
      void setOpInt1_Number(int value);
      int getOpInt2_Move() const;
      void setOpInt2_Move(int value);
      int getOpInt3_Attack() const;
      void setOpInt3_Attack(int value);
      int getOpInt_Number() const;
      void setOpInt_Number(int value);
private:
      Monster*mon_BeingSelected=NULL;
      Monster*mon_BeingAttack=NULL;
    bool stage_ButtonOnly=0;
    bool stage_Initial=0;
    bool stage_Move=0;
    bool stage_ChooseMon=0;
    bool stage_AIturn=0;
    bool stage_Skill=0;
    bool stage_ChooseSkill=0;
    bool stage_ChooseSkillMon=0;
    bool stage_Over=0;
    bool nextIsToSelect=0;
    int  mon_OnStage=0;
    Square* shining_Place;
//    Square* square_changing[5];
    int opInt_Number=0;//skillNumber 1 or 2;
    int opInt1_Number=0;//1,2,3,4
    int opInt2_Move=1;
    int opInt3_Attack=1;
};



#endif // BATTLESCENE_H
