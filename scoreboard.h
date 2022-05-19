#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "playercontroller.h"
#include "AIcontroller.h"

class ScoreBoard: public Component
{
public:
    ScoreBoard(PlayerController *player);

    void onAttach() override;
    void onUpdate(float deltatime) override;

protected:
    PlayerController *player = nullptr;
    ImageTransform *imagetransform;
    QGraphicsSimpleTextItem *text = nullptr;
    //QString name;
    QString health;
    QString score;
    bool update = true;
};

#endif // SCOREBOARD_H
