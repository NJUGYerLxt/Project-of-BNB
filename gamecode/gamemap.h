#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"

class Gamemap
{
public:
    Gamemap(GameScene *gameScene);

private:
    GameObject *block[15][20];
};

#endif // GAMEMAP_H
