#ifndef TOOL_H
#define TOOL_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "imagetransform.h"

class Tool: public Component
{
public:
    Tool(int type);

    void onAttach() override;
    void onFirstUpdate() override;
    void onUpdate(float deltatime) override;

protected:
    int type;
    ImageTransform *imagetransform;
    QGraphicsItem *collider = nullptr;
    const int pickuptools = 15;
};

#endif // TOOL_H
