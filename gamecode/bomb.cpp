#include "bomb.h"

Bomb::Bomb()
{

}

void Bomb::setMaster(PlayerController *master) {this->master = master;}

PlayerController *Bomb::getMaster() {return master;}

void Bomb::onAttach()
{
    //bomb = this->gameObject;
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    //assert(bomb != nullptr);
    assert(imagetransform != nullptr);
}

void Bomb::explode(float deltatime)
{
    imagetransform->setImage(":/images/gamecode/map/bombing.png");
    cooldown -= deltatime;
    if (cooldown <= 0)
        destory(this->gameObject);
}

void Bomb::onUpdate(float deltatime)
{
    countdown -= deltatime;
    if (countdown <= 0)
    {
        if (!ChangeCondition)
        {
            master->ModifyCurBombNum();
            ChangeCondition = true;
        }
        explode(deltatime);
    }
}

void Bomb::Modifyrange()
{
    range++;
}
