#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "setbomb.h"

class PlayerController: public Component
{
public:
    PlayerController(int type);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

private:
    int type;
    Physics *physics;
    SetBomb *setbomb;
};

#endif // PLAYERCONTROLLER_H
