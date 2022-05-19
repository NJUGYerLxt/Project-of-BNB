#ifndef BOMB_H
#define BOMB_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"
#include "playercontroller.h"

class Bomb: public Component
{
public:
    Bomb();
    void setMaster(PlayerController *master);
    void setRange(int range);
    void setVelocity(QPointF velocity);
    void setPushable();
    PlayerController *getMaster();
    void onAttach() override;
    void onUpdate(float deltatime) override;
    bool getDestoried();
    int getRange();

protected:
    const float bombtime = 2.5;
    const float cooltime = 1;
    const float changetime = 0.5;
    float change = changetime;
    float cooldown = cooltime;
    float countdown = bombtime;
    void explode(float deltatime);
    QGraphicsItem *collider;
    ImageTransform *imagetransform = nullptr;
    //ImageTransform *detector = nullptr;
    PlayerController *master;
    int range = 1;
    QPointF velocity = QPointF(0, 0);

private:
    bool ChangeCondition = false;
    bool GenerateLight = false;
    bool Destoried = false;
    bool pushable = false;
    int condition = 0;
    const int hitplayer = 200;
    const int hitsoftwall = 10;
};

#endif // BOMB_H
