#ifndef DIALOGUE_H
#define DIALOGUE_H

#include"mytextitem.h"
#include"mainscene.h"
#include"button.h"
#include"battlescene.h"
#include<QObject>
class Dialogue :public QObject,public QGraphicsRectItem
{Q_OBJECT
public:
    Dialogue(Mainscene* scene_Dialogueindefault);
    Dialogue(BattleScene* scene_Dialogueindefault);

    MyTextItem *Dialogue_TextItem;
    class Character* dialogue_char=NULL;
  void setTextItem(MyTextItem *textItem_toshow);
  void setButton(Button *button,int bx,int by);
  Mainscene* scene_DialogueinM;
  BattleScene* scene_DialogueinB;
//events
  void keyPressEvent(QKeyEvent *event);

signals:
  void Toscene_removehero();

};

#endif // DIALOGUE_H
