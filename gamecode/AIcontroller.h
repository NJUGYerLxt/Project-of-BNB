#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "bomb.h"

class AIController: public Component
{
public:
    AIController();

    void onAttach() override;
    void onUpdate(float deltaTime) override;

private:
    Physics *physics;
};

#endif // AICONTROLLER_H
