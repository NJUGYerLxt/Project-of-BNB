#ifndef HEALTH_H_
#define HEALTH_H_

#include "hitable.h"

class Health : public Hitable
{
public:
    explicit Health(int health);
    //Health(GameScene *gamescene);
    void beHit() override;
    //void onAttach() override;
    void onUpdate(float deltatime) override;
    int gethealth();

protected:
    int health;
    int presenttime = 1;
    GameScene *gameScene;
};

#endif  // HEALTH_H_
