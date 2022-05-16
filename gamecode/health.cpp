#include "health.h"
#include "wall.h"
#include "playercontroller.h"

Health::Health(int health) : health(health) {}

void Health::beHit() {
  health--;
  if (health <= 0)
  {
      if (this->gameObject->getComponent<PlayerController>() != nullptr)
      {
          this->gameObject->getComponent<PlayerController>()->Death();
          this->gameObject->getComponent<Physics>()->setVelocity(0, 0);
      }
      else
          destory(this->gameObject);
  }
}

void Health::onAttach()
{
    if (health > 0)
        return;
    if (this->gameObject->getComponent<PlayerController>() != nullptr)
       this->gameObject->getComponent<ImageTransform>()->setImage(":/images/gamecode/player/death.png");
}

void Health::onUpdate(float deltatime)
{
    if (health > 0)
        return;
    presenttime -= deltatime;
    if (presenttime <= 0)
        destory(this->gameObject);
}

int Health::gethealth() {return health;}
