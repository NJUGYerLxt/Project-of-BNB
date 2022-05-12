#include "AIcontroller.h"

AIController::AIController() {}

void AIController::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    assert(physics != nullptr);
}

void AIController::onUpdate(float deltatime)
{

}
