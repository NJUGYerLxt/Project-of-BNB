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

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    Transform *transform = nullptr;
    ImageTransform *imagetransform = nullptr;
    QGraphicsItem *collider = nullptr;
    Physics *physics;


private:
    int type;
    int MostBombnum = 1;
    int curBombnum = 0;
};

#endif // PLAYERCONTROLLER_H
