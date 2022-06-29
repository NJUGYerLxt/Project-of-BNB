#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "bomb.h"
#include "playercontroller.h"
#include "gamemap.h"

class AIController: public PlayerController
{
public:
    AIController(int type);
    void ConnectPlayer(PlayerController *player1, PlayerController *player2, PlayerController *player3);
    void ConnectGameScene(GameScene *gamescene);
    void ConnectGamemap(Gamemap *gamemap);
    //void InsertBomb(Bomb *bomb);
    //void RemoveBomb(Bomb *bomb);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    Physics *physics;
    GameScene *gamescene = nullptr;
    Gamemap *gamemap = nullptr;
    Health *health;
    void observe();
    bool moveunit();
    int type;
    int velocity = 160;
    int decision;
    int score = 0;
    int pic[15][20]; //0地砖 1软墙 2硬墙 3玩家 4炸弹 5道具
    PlayerController *player1 = nullptr, *player2 = nullptr, *player3 = nullptr;
    struct bomb
    {
        QPointF loc;
        int range;
        float countdown;
    };
    struct tool
    {
        QPointF loc;
        int type;
    };
    QList<bomb> bomblist;
    QList<tool> toollist;
};

#endif // AICONTROLLER_H
