#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"
#include "health.h"
#include "wall.h"

class Gamemap
{
public:
    Gamemap(GameScene *gameScene);
    GameObject *getblock(int i, int j);
    QPointF getblocklocation(int i, int j);

private:
    GameObject *block[15][20];
    QPointF location[15][20];
};

#endif // GAMEMAP_H
