#ifndef STOPBUTTON_H
#define STOPBUTTON_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"
#include "playercontroller.h"

class StopButton: public Component
{
public:
    StopButton(GameScene *gameScene);

    void onAttach() override;
    void onUpdate(float deltatime) override;
    void onClick(QGraphicsSceneMouseEvent *ev) override;

protected:
    ImageTransform *imagetransform;
    GameScene *gameScene;
    bool stop = false;
};

#endif // STOPBUTTON_H
