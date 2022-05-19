#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "bomb.h"
#include "playercontroller.h"

class AIController: public PlayerController
{
public:
    AIController(int type);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    Physics *physics;
    int type;
    int velocity = 160;
    float timeunit = 10 / velocity;
    float curtime = timeunit;
    int decision;
    int score = 0;
};

#endif // AICONTROLLER_H
