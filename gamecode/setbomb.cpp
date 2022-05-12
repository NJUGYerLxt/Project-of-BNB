#include "setbomb.h"

SetBomb::SetBomb() {}

void SetBomb::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    assert(physics != nullptr);
}

void SetBomb::onUpdate(float deltatime)
{
    countdown -= deltatime;
    if (countdown > 0)  return;

}
