#include "playercontroller.h"
#include "bomb.h"

PlayerController::PlayerController(int type)
{
    this->type = type;
}

void PlayerController::ModifyCurBombNum()
{
    assert(curBombnum > 0);
    curBombnum--;
}

void PlayerController::ModifyMostBombNum() {MostBombnum++;}

void PlayerController::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    transform = this->gameObject->getComponent<Transform>();
    assert(physics != nullptr);
    assert(transform != nullptr);
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
            if (curBombnum >= MostBombnum)
                return;
            auto bomb = new GameObject();
            auto classification = new Bomb();
            classification->setMaster(this);
            bomb->addComponent(classification);
            bomb->addComponent(new Transform(this->transform->pos()));
            attachGameObject(bomb);
            curBombnum++;
        }
        break;
    case 2:
        if (getKey(Qt::Key_Left))  vx -= 80;
        if (getKey(Qt::Key_Right))  vx += 80;
        if (getKey(Qt::Key_Up))  vy -= 80;
        if (getKey(Qt::Key_Down))  vy += 80;
        if (getKey(Qt::Key_Return))
        {
            if (curBombnum >= MostBombnum)
                return;
            auto bomb = new GameObject();
            auto classification = new Bomb();
            classification->setMaster(this);
            bomb->addComponent(classification);
            bomb->addComponent(new Transform(this->transform->pos()));
            attachGameObject(bomb);
            curBombnum++;
        }
        break;
    }
    physics->setVelocity(vx, vy);
}
