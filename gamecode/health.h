#ifndef HEALTH_H_
#define HEALTH_H_

#include "hitable.h"

class Health : public Hitable
{
public:
    explicit Health(int health);
    void beHit() override;
    void onUpdate(float deltatime) override;
    int gethealth();

protected:
    int health;
    int presenttime = 20;
    GameScene *gameScene;
};

#endif  // HEALTH_H_
