#include "hitable.h"
#include "wall.h"

Hitable::Hitable() {}

void Hitable::beHit()
{
    if (this->gameObject->getComponent<Wall>() != nullptr)
    {
        this->gameObject->getComponent<ImageTransform>()->setImage(":/images/gamecode/map/floor.png");
        this->gameObject->removeComponent(this->gameObject->getComponent<Wall>());
    }
    else
      destory(this->gameObject);
}
