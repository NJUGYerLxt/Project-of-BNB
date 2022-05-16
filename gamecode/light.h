#ifndef LIGHT_H
#define LIGHT_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"
#include "playercontroller.h"
#include "bomb.h"

class Light: public Bomb
{
public:
    Light(Bomb *parentBomb);
    void setType(int type);
    void onAttach() override;
    void onUpdate(float deltatime) override;
    bool gethit();

protected:
    ImageTransform *imagetransform = nullptr;
    Bomb *parentBomb;
    QGraphicsItem *collider = nullptr;
    int type;
    bool attached = false;
    bool hit = false;
};

#endif // LIGHT_H
