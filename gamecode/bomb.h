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
    void Modifyrange();
    void onAttach() override;
    void onUpdate(float deltatime) override;
    bool getDestoried();

protected:
    const float bombtime = 2.5;
    const float cooltime = 1;
    float cooldown = cooltime;
    float countdown = bombtime;
    void explode(float deltatime);
    QGraphicsItem *collider;
    ImageTransform *imagetransform = nullptr;
    ImageTransform *detector = nullptr;
    PlayerController *master;
    int range = 1;

private:
    bool ChangeCondition = false;
    bool GenerateLight = false;
    bool Destoried = false;
};

#endif // BOMB_H
