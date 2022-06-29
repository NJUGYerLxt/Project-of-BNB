#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"
#include "health.h"
#include "wall.h"

class Gamemap
{
public:
    Gamemap(GameScene *gameScene);
    GameObject *getblock(int i, int j);
    QPointF getblocklocation(int i, int j);
    int getcontent(int i, int j);
    void InsertBomb(QPointF loc, int range, float time);

private:
    struct bomb
    {
        QPointF loc;
        int range;
        float inserttime;
    };
    QList<bomb> bomblist;
    int content[15][20]; //0地砖 1软墙 2硬墙
    GameObject *block[15][20];
    QPointF location[15][20];
    bool check();
    bool flag = false;
};

#endif // GAMEMAP_H
