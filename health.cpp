#include "health.h"
#include "wall.h"
#include "playercontroller.h"

Health::Health(int health) : health(health) {}

void Health::beHit() {
  if (health >= 0)
      health--;
  if (health <= 0)
  {
      if (this->gameObject->getComponent<PlayerController>() != nullptr)
      {
          this->gameObject->getComponent<PlayerController>()->Death();
          this->gameObject->getComponent<Physics>()->setVelocity(0, 0);
          this->gameObject->getComponent<ImageTransform>()->setImage(":/images/images/player/death.png");
      }
      else
          destory(this->gameObject);
  }
}

void Health::onUpdate(float deltatime)
{
    if (health > 0)
    {
        presenttime += deltatime;
        return;
    }
    presenttime -= deltatime;
    if (presenttime <= 0 && this->gameObject->getComponent<PlayerController>() != nullptr)
        detachGameObject(this->gameObject);
}

int Health::gethealth() {return health;}
