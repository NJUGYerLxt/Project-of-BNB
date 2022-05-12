#ifndef SETBOMB_H
#define SETBOMB_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"

class SetBomb: public Component
{
public:
    SetBomb();

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    const float bombtime = 3;
    float countdown = bombtime;

private:
    Physics *physics;
};

#endif // SETBOMB_H
