#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "wall.h"
#include "gamemap.h"

class PlayerController: public Component
{
public:
    PlayerController(int type);
    QPointF getpos();
    int gettype();
    void ConnectGameScene(GameScene *gamescene);
    void ConnectGamemap(Gamemap *gamemap);
    void ModifyCurBombNum();
    void ModifyMostBombNum();
    void ModifyVelocity();
    void ModifyBombRange();
    void ModifyPushBomb();
    void ModifyScore(int score);
    int getScore();

    void onAttach() override;
    void onUpdate(float deltaTime) override;
    void Death();
    bool getdeath();

protected:
    GameScene *gamescene = nullptr;
    Gamemap *gamemap = nullptr;
    ImageTransform *imagetransform = nullptr;
    QGraphicsItem *collider = nullptr;
    Physics *physics;
    QPointF getLoc(QPointF pos);
    int velocity = 160;
    int MostBombnum = 1;
    int curBombnum = 0;
    int BombRange = 1;
    int score = 0;
    bool dead = false;
    bool pushbomb = false;
    int type;

private:
    const int interval = 1;
    int curinterval = interval;
};

#endif // PLAYERCONTROLLER_H
