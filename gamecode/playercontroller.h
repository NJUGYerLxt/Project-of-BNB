#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"

class PlayerController: public Component
{
public:
    PlayerController(int type);
    void ModifyCurBombNum();
    void ModifyMostBombNum();

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    Transform *transform;

private:
    int type;
    Physics *physics;
    int MostBombnum = 1;
    int curBombnum = 0;
};

#endif // PLAYERCONTROLLER_H
