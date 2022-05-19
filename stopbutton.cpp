#include "stopbutton.h"

StopButton::StopButton(GameScene *gameScene) {this->gameScene = gameScene;}

void StopButton::onAttach()
{
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    assert(imagetransform != nullptr);
    imagetransform->setFiltersChildEvents(true);
}

void StopButton::onUpdate(float deltatime) {}

void StopButton::onClick(QGraphicsSceneMouseEvent *ev)
{
    if (!stop)
    {
        gameScene->StopUpdate();
        stop = true;
    }
    else
    {
        gameScene->BeginUpdate();
        stop = false;
    }
}
