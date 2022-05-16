#ifndef HEALTH_H_
#define HEALTH_H_

#include "hitable.h"

class Health : public Hitable
{
public:
    explicit Health(int health);

    void beHit() override;
    void onAttach() override;
    void onUpdate(float deltatime) override;
    int gethealth();

protected:
    int health;
    int presenttime = 1;
};

#endif  // HEALTH_H_
