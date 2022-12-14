#ifndef HITABLE_H_
#define HITABLE_H_

#include "component.h"
#include "gamescene.h"
#include "gameobject.h"
#include "imagetransform.h"
#include "transform.h"

class Hitable : public Component
{
public:
    Hitable();
    virtual void beHit();
    void setGameScene(GameScene *gameScene);
    //void ConnectGamemap(Gamemap *gamemap);
    //void onAttach() override;

protected:
    //bool generatetool = false;
    //int generate;
    GameScene *gameScene;
    //Gamemap *gamemap;
};

#endif  // HITABLE_H_
