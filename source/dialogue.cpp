#include"dialogue.h"
#include"mainscene.h"
#include"scene0.h"
#include"myview.h"
#include<QBrush>
#include<QKeyEvent>
#include<QDebug>
#include<QColor>
#include<QTimer>
extern Myview* view;
Dialogue::Dialogue(Mainscene *scene_Dialogueindefault)
{
    scene_DialogueinM=scene_Dialogueindefault;
    scene_DialogueinB=NULL;
    setRect(0,0,780,100);
    QBrush brush;
    brush.setStyle(Qt::Dense4Pattern);
    brush.setColor(QColor(250,250,250));
    setBrush(brush);
    //    setZValue();
}

Dialogue::Dialogue(BattleScene *scene_Dialogueindefault)
{
    scene_DialogueinB=scene_Dialogueindefault;
    scene_DialogueinM=NULL;
    setRect(0,0,780,100);
    QBrush brush;
    brush.setStyle(Qt::Dense4Pattern);
    brush.setColor(QColor(250,250,250));
    setBrush(brush);
}

void Dialogue::setTextItem(MyTextItem* textItem_toshow)
{
     Dialogue_TextItem=textItem_toshow;
     Dialogue_TextItem->setPos(x()+20,y()+20);
     Dialogue_TextItem->setTextWidth(740);

}

void Dialogue::setButton(Button *button, int bx, int by)
{
    button->setParent(this);
    scene_DialogueinB->addItem(button);
    button->setPos(x()+bx,y()+by);
}

void Dialogue::keyPressEvent(QKeyEvent *event)
{
 if(event->key()==Qt::Key_Return)
 {
      if(Dialogue_TextItem->speakOver())
      {
        scene_DialogueinM->removeDialogue();
        if(dialogue_char!=NULL)
        {
          if(dialogue_char->char_charData!=NULL)
          {
              dynamic_cast<Mainscene*>(view->scene())->scene_hero->clearFocus();
              view->setSceneAndBGM();
              view->set_bgm("qrc:/sounds/sounds/battle1.mp3");
              scene_DialogueinM->sleep(2000);
              view->setBattleScene(*dialogue_char->char_charData);
              dialogue_char->char_charData=NULL;
              dialogue_char=NULL;
              scene_DialogueinM->scene_NPC=NULL;
              return;
          }
          else{dialogue_char=NULL;scene_DialogueinM->scene_NPC=NULL;return;}
        }
        else{return;}
      }

      else
      {
         if(dialogue_char!=NULL)
          {scene_DialogueinM->removeItem(scene_DialogueinM->scene_head_Now);}
         Dialogue_TextItem->setNextToSay();
         switch (Dialogue_TextItem->getNextToSay().inf_HeadNumber)
         {
         case -2: scene_DialogueinM->scene_head_Now=NULL;break;
         case -1:
                  scene_DialogueinM->scene_head_Now=scene_DialogueinM->scene_hero_head;
                  scene_DialogueinM->addItem(scene_DialogueinM->scene_head_Now);
                  scene_DialogueinM->scene_head_Now->setPos(view->sceneRect().x()+20,view->sceneRect().y()+300);
                  break;
         case 0 :
                  scene_DialogueinM->scene_head_Now=scene_DialogueinM->scene_NPC->char_head[0];
                  scene_DialogueinM->addItem(scene_DialogueinM->scene_head_Now);
                  scene_DialogueinM->scene_head_Now->setPos(view->sceneRect().x()+580,view->sceneRect().y()+300);
                  break;
         case 1 :
                  scene_DialogueinM->scene_head_Now=scene_DialogueinM->scene_NPC->char_head[1];
                  scene_DialogueinM->addItem(scene_DialogueinM->scene_head_Now);
                  scene_DialogueinM->scene_head_Now->setPos(view->sceneRect().x()+20,view->sceneRect().y()+300);
                  break;
         default:qDebug()<<"IngNumber error";break;
         }

         return;

      }
  }

   else return;
}






