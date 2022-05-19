#ifndef PHYSICS_H
#define PHYSICS_H

#include "gamescene.h"
#include "gameobject.h"
#include "component.h"
#include "transform.h"
#include "transformbuilder.h"

class Physics: public Component
{
public:
    Physics();

    void onAttach() override;
    void onUpdate(float deltaTime) override;

    void setVelocity(float vx, float vy);
    QPointF getVelocity();

private:
    Transform *transform;
    float vx = 0, vy = 0;
};

#endif // PHYSICS_H
