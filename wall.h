#ifndef WALL_H
#define WALL_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"
#include "health.h"

class Wall: public Component
{
public:
    Wall();
};

#endif // WALL_H
