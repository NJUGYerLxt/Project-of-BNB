#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"

class Gamemap: public Component
{
public:
    Gamemap();

    void onAttach() override;
    void onUpdate(float deltatime) override;

protected:
    GameObject *pic[15][20];
};

#endif // GAMEMAP_H
