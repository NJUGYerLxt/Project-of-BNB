#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "wall.h"

class PlayerController: public Component
{
public:
    PlayerController(int type);
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

protected:
    ImageTransform *imagetransform = nullptr;
    QGraphicsItem *collider = nullptr;
    Physics *physics;
    int MostBombnum = 1;
    int curBombnum = 0;
    int velocity = 160;
    int BombRange = 1;
    int score = 0;
    bool dead = false;
    bool pushbomb = false;

private:
    int type;
    const int interval = 1;
    int curinterval = interval;
};

#endif // PLAYERCONTROLLER_H
