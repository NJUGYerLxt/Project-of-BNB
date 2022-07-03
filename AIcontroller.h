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

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    Physics *physics;
    GameScene *gamescene = nullptr;
    Gamemap *gamemap = nullptr;
    Health *health;

//    void changevelocity(int v);
//    void changepushbomb();

    void checkcollide();
    QPointF CalPlayerLoc(QPointF pos);
    void observe();
    void moveunit(int dir); //1上 2下 3左 4右
    bool moveable(float deltatime);
    const float moveunittime = 0.5;
    const float safecountdown = 0.5;
    float curmovetime = moveunittime;
    int safe(int x, int y, int step); //0潜在不安全  1安全  -1不可走 2必死
    int pic[15][20]; //0地砖 1软墙 2硬墙 3玩家 4炸弹 5道具

    PlayerController *player1 = nullptr, *player2 = nullptr, *player3 = nullptr;
    struct bomb
    {
        QPointF loc;
        int range;
        float countdown;
        int master;
        bool pushable;
    };
    struct tool
    {
        QPointF loc;
        int type;
    };
    struct light
    {
        QPointF loc;
    };
    QList<bomb> bomblist;
    QList<tool> toollist;
    QList<light> lightlist;
    void bfs(int x, int y, bool risk);
    int steps[15][20];
    QPointF pre[15][20];

    void moveaway(int x, int y, float deltatime);
    void randomwalk(float deltatime);
    bool move(int startx, int starty, int endx, int endy, float deltatime);
    bool escape(int x, int y, float deltatime);
    bool picktools(int x, int y, float deltatime, bool attack);
    bool setbomb(int x, int y);
    bool bombsoftwall(int x, int y, float deltatime);
    bool closeattack(int x, int y);
    int farattack(int x, int y); //0不可行 1向上 2向下 3向左 4向右
    bool PushBomb(int x, int y, bool attack);
};

#endif // AICONTROLLER_H
