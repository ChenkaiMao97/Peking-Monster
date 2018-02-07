#ifndef MYVIEW_H
#define MYVIEW_H

#include"mainscene.h"
#include"monster.h"
#include"battlescene.h"
#include"People.h"
#include<QGraphicsView>
#include<QObject>
#include<QMediaPlayer>

class Myview: public QGraphicsView
{Q_OBJECT
public:
    Myview(QGraphicsView *parent=0);
    QMediaPlayer *view_bgm;
    QMediaPlaylist *playlist;
    playerData *view_hero;
    QGraphicsPixmapItem* view_hero_PixMap=NULL;
    BattleScene* view_BS;
    QGraphicsPixmapItem* head_You=NULL;

    void setSceneAndBGM();
    void setsceneBackto(Mainscene* scene);
    void setBgmBackTo(QString bgmB);

public slots:
    void set_scene(Mainscene *scene_show);
    void item_at(QPointF point);
    void set_bgm(QString url);
    void setBattleScene(studentData &stu);
    void setBattleScene(characterData &character);
    void setRandomBS();
    void setInitial();
    void setMainscene();
    void setBagScene();

signals:
    void signaltohero(bool,bool);

private:
    Mainscene* scene_BackTo;
    QString bgm_BackTo;
};


#endif // MYVIEW_H
