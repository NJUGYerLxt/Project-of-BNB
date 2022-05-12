#include "playercontroller.h"

PlayerController::PlayerController(int type)
{
    this->type = type;
}

void PlayerController::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    assert(physics != nullptr);
}

void PlayerController::onUpdate(float deltatime)
{
    float vx = 0, vy = 0;
    switch (type)
    {
    case 1:
        if (getKey(Qt::Key_A))  vx -= 80;
        if (getKey(Qt::Key_D))  vx += 80;
        if (getKey(Qt::Key_W))  vy -= 80;
        if (getKey(Qt::Key_S))  vy += 80;
        if (getKey(Qt::Key_Space))
        {

        }
        break;
    case 2:
        if (getKey(Qt::Key_Left))  vx -= 80;
        if (getKey(Qt::Key_Right))  vx += 80;
        if (getKey(Qt::Key_Up))  vy -= 80;
        if (getKey(Qt::Key_Down))  vy += 80;
        if (getKey(Qt::Key_Enter))
        {

        }
        break;
    }
    physics->setVelocity(vx, vy);
}
