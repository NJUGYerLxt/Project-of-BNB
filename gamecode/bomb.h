#ifndef BOMB_H
#define BOMB_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"
#include "playercontroller.h"

class Bomb: public Component
{
public:
    Bomb();
    void setMaster(PlayerController *master);
    PlayerController *getMaster();

    void onAttach() override;
    void onUpdate(float deltatime) override;

protected:
    const float bombtime = 2.5;
    const float cooltime = 1;
    float cooldown = cooltime;
    float countdown = bombtime;
    void explode(float deltatime);

private:
    //GameObject *bomb = nullptr;
    Transform *transform = nullptr;
    PlayerController *master;
    bool ChangeCondition = false;
};

#endif // BOMB_H
