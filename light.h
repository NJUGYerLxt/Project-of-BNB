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

class Light: public Component
{
public:
    Light(Bomb *bomb);
    void onAttach() override;
    void onFirstUpdate() override;
    void onUpdate(float deltatime) override;
    bool gethitwall();
    void setCurRange(int range);
    void setDirection(int direction);
    QPointF getpos();

protected:
    ImageTransform *imagetransform = nullptr;
    PlayerController *player = nullptr;
    Bomb *parentBomb = nullptr;
    QGraphicsItem *collider = nullptr;
    int type;
    int currange;
    int direction;  //1上 2下 3左 4右
    bool hitwall = false;
    bool generate = false;
    const int hitplayer = 200;
    const int hitsoftwall = 10;
    const int pickuptools = 15;
};

#endif // LIGHT_H
