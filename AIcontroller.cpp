#include "AIcontroller.h"
#include "tool.h"
#include <QStack>

AIController::AIController(int type) : PlayerController(type) {this->type = type;}

void AIController::ConnectPlayer(PlayerController *player1, PlayerController *player2,
                                 PlayerController *player3)
{
    this->player1 = player1;
    this->player2 = player2;
    this->player3 = player3;
}

void AIController::ConnectGameScene(GameScene *gamescene) {this->gamescene = gamescene;}

void AIController::ConnectGamemap(Gamemap *gamemap) {this->gamemap = gamemap;}

void AIController::moveunit(int dir)
{
    if (health->gethealth() <= 0)
    {
        physics->setVelocity(0, 0);
        imagetransform->setImage(":/pictures/images/player/death.png");
        return;
    }
    float vx = 0, vy = 0;
    switch (type)
    {
    case 3:
        if (dir == 0)
        {
            vx = 0;  vy = 0;
        }
        else if (dir == 1)
        {
            vy -= velocity;
            imagetransform->setImage(":/pictures/images/player/3-up.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-30)
                        && transform->pos().y() - imagetransform->pos().y() < 0)
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vy < 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(0, -240));
                    }
                    if (vy < 0)  vy = 0;
                }
            }
        }
        else if (dir == 2)
        {
            vy += velocity;
            imagetransform->setImage(":/pictures/images/player/3-down.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(44)
                        && transform->pos().y() - imagetransform->pos().y() > 15)
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vy > 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(0, 240));
                    }
                    if (vy > 0)  vy = 0;
                }
            }
        }
        else if (dir == 3)
        {
            vx -= velocity;
            imagetransform->setImage(":/pictures/images/player/3-left.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && imagetransform->pos().x() - transform->pos().x() < qreal(40)
                        && transform->pos().x() - imagetransform->pos().x() < qreal(-5)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vx < 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(-240, 0));
                    }
                    if (vx < 0)  vx = 0;
                }
            }
        }
        else if (dir == 4)
        {
            vx += velocity;
            imagetransform->setImage(":/pictures/images/player/3-right.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && transform->pos().x() - imagetransform->pos().x() < qreal(40)
                        && transform->pos().x() - imagetransform->pos().x() > qreal(5)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vx > 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(240, 0));
                    }
                    if (vx > 0)  vx = 0;
                }
            }
        }
        break;
    case 4:
        if (dir == 0)
        {
            vx = 0;  vy = 0;
        }
        else if (dir == 1)
        {
            vy -= velocity;
            imagetransform->setImage(":/pictures/images/player/4-up.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-30)
                        && transform->pos().y() - imagetransform->pos().y() < 0)
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vy < 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(0, -240));
                    }
                    if (vy < 0)  vy = 0;
                }
            }
        }
        else if (dir == 2)
        {
            vy += velocity;
            imagetransform->setImage(":/pictures/images/player/4-down.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(44)
                        && transform->pos().y() - imagetransform->pos().y() > 15)
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vy > 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(0, 240));
                    }
                    if (vy > 0)  vy = 0;
                }
            }
        }
        else if (dir == 3)
        {
            vx -= velocity;
            imagetransform->setImage(":/pictures/images/player/4-left.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && imagetransform->pos().x() - transform->pos().x() < qreal(40)
                        && transform->pos().x() - imagetransform->pos().x() < qreal(-5)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vx < 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(-240, 0));
                    }
                    if (vx < 0)  vx = 0;
                }
            }
        }
        else if (dir == 4)
        {
            vx += velocity;
            imagetransform->setImage(":/pictures/images/player/4-right.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && transform->pos().x() - imagetransform->pos().x() < qreal(40)
                        && transform->pos().x() - imagetransform->pos().x() > qreal(5)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vx > 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(240, 0));
                    }
                    if (vx > 0)  vx = 0;
                }
            }
        }
        break;
    }
    physics->setVelocity(vx, vy);
}

void AIController::checkcollide()
{
    float vx, vy;
    vx = physics->getVelocity().x();
    vy = physics->getVelocity().y();
    if (vx > 0 && vy == 0)
    {
        for (auto item : this->collider->collidingItems())
        {
            while (item->parentItem() != nullptr)
                item = item->parentItem();
            auto transform = dynamic_cast<Transform *>(item);
            if (transform != nullptr && transform->pos().x() - imagetransform->pos().x() < qreal(40)
                    && transform->pos().x() - imagetransform->pos().x() > qreal(5)
                    && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                    && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
            {
                auto object = transform->getParentGameObject();
                auto wall = object->getComponent<Wall>();
                auto bomb = object->getComponent<Bomb>();
                if (wall == nullptr && bomb == nullptr)  continue;
                if (bomb != nullptr && vx > 0 && pushbomb && bomb->getMaster() == this)
                {
                    bomb->setVelocity(QPointF(240, 0));
                }
                if (vx > 0)  vx = 0;
            }
        }
    }
    else if (vx < 0 && vy == 0)
    {
        for (auto item : this->collider->collidingItems())
        {
            while (item->parentItem() != nullptr)
                item = item->parentItem();
            auto transform = dynamic_cast<Transform *>(item);
            if (transform != nullptr && imagetransform->pos().x() - transform->pos().x() < qreal(40)
                    && transform->pos().x() - imagetransform->pos().x() < qreal(-5)
                    && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                    && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
            {
                auto object = transform->getParentGameObject();
                auto wall = object->getComponent<Wall>();
                auto bomb = object->getComponent<Bomb>();
                if (wall == nullptr && bomb == nullptr)  continue;
                if (bomb != nullptr && vx < 0 && pushbomb && bomb->getMaster() == this)
                {
                    bomb->setVelocity(QPointF(-240, 0));
                }
                if (vx < 0)  vx = 0;
            }
        }
    }
    else if (vy > 0 && vx == 0)
    {
        for (auto item : this->collider->collidingItems())
        {
            while (item->parentItem() != nullptr)
                item = item->parentItem();
            auto transform = dynamic_cast<Transform *>(item);
            if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                    && transform->pos().y() - imagetransform->pos().y() < qreal(44)
                    && transform->pos().y() - imagetransform->pos().y() > 15)
            {
                auto object = transform->getParentGameObject();
                auto wall = object->getComponent<Wall>();
                auto bomb = object->getComponent<Bomb>();
                if (wall == nullptr && bomb == nullptr)  continue;
                if (bomb != nullptr && vy > 0 && pushbomb && bomb->getMaster() == this)
                {
                    bomb->setVelocity(QPointF(0, 240));
                }
                if (vy > 0)  vy = 0;
            }
        }
    }
    else if (vy < 0 && vx == 0)
    {
        for (auto item : this->collider->collidingItems())
        {
            while (item->parentItem() != nullptr)
                item = item->parentItem();
            auto transform = dynamic_cast<Transform *>(item);
            if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                    && transform->pos().y() - imagetransform->pos().y() > qreal(-30)
                    && transform->pos().y() - imagetransform->pos().y() < 0)
            {
                auto object = transform->getParentGameObject();
                auto wall = object->getComponent<Wall>();
                auto bomb = object->getComponent<Bomb>();
                if (wall == nullptr && bomb == nullptr)  continue;
                if (bomb != nullptr && vy < 0 && pushbomb && bomb->getMaster() == this)
                {
                    bomb->setVelocity(QPointF(0, -240));
                }
                if (vy < 0)  vy = 0;
            }
        }
    }
    physics->setVelocity(vx, vy);
}

bool AIController::moveable(float deltatime)
{
    curmovetime -= deltatime;
    if (curmovetime > 0)
        return false;
    QPointF curpos = imagetransform->pos();
    bool flag = false;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            int x = j * 40 + 20;
            int y = i * 40 + 15;
            if (abs(curpos.x() - x) <= 5 && curpos.y() - y <= 0 && curpos.y() - y >= -5)
            {
                flag = true;
                break;
            }
        }
        if (flag)  break;
    }
    return flag;
}

void AIController::randomwalk(float deltatime)
{
    int dir = rand() % 5;
    if (moveable(deltatime))
        moveunit(dir);
}

void AIController::observe()
{
    int i, j;
    QPointF pos;
    QList <GameObject *> gameObjects;
    bomblist.clear();
    toollist.clear();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 20; j++)
            pic[i][j] = gamemap->getcontent(i, j);
    pos = player1->getpos();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 20; j++)
            if (pos.x() - (j * 40 + 20) >= -20 && pos.x() - (j * 40 + 20) < 20
                    && pos.y() - (i * 40 + 20) >= -20 && pos.y() - (i * 40 + 20) < 20)
            {
                pic[i][j] = 3;
                break;
            }

    pos = player2->getpos();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 20; j++)
            if (pos.x() - (j * 40 + 20) >= -20 && pos.x() - (j * 40 + 20) < 20
                    && pos.y() - (i * 40 + 20) >= -20 && pos.y() - (i * 40 + 20) < 20)
            {
                pic[i][j] = 3;
                break;
            }

    pos = player3->getpos();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 20; j++)
            if (pos.x() - (j * 40 + 20) >= -20 && pos.x() - (j * 40 + 20) < 20
                    && pos.y() - (i * 40 + 20) >= -20 && pos.y() - (i * 40 + 20) < 20)
            {
                pic[i][j] = 3;
                break;
            }
    gameObjects = gamescene->getgameObjects();
    for (i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i]->getComponent<Bomb>() != nullptr)
        {
            bomb newbomb;
            auto curbomb = gameObjects[i]->getComponent<Bomb>();
            newbomb.loc = QPointF((curbomb->getpos().y() - 20)/40,
                                  (curbomb->getpos().x() - 20)/40);
            newbomb.range = curbomb->getRange();
            newbomb.countdown = curbomb->getCountdown();
            bomblist.append(newbomb);
        }
        else if (gameObjects[i]->getComponent<Tool>() != nullptr)
        {
            tool newtool;
            auto curtool = gameObjects[i]->getComponent<Tool>();
            newtool.loc = QPointF((curtool->getpos().y() - 20)/40,
                                  (curtool->getpos().x() - 20)/40);
            newtool.type = curtool->getType();
            toollist.append(newtool);
        }
    }
}

int AIController::safe(int x, int y, int step)
{
    int xx[5] = {0, 0, 0, 1, -1}; //坐标
    int yy[5] = {0, -1, 1, 0, 0};  //坐标
    int i, j, k, l;
    int flag;
    if (pic[x][y] == 1 || pic[x][y] == 2)
        return -1;
    bool hitbomb;
    for (i = 0; i < bomblist.size(); i++)
    {
        if (bomblist[i].loc.x() == x && bomblist[i].loc.y() == y)
            return 0;
        for (j = 0; j <= 4; j++)
        {
            for (k = 1; k <= bomblist[i].range; k++)
            {
                hitbomb = false;
                for (l = 0; l < bomblist.size(); l++)
                {
                    if (j != 0 && bomblist[l].loc.x() == bomblist[i].loc.x()+k*yy[j] &&
                            bomblist[l].loc.y() == bomblist[i].loc.y()+k*xx[j])
                    {
                        hitbomb = true;
                        break;
                    }
                }
                int h = bomblist[i].loc.x()+k*yy[j];
                int l = bomblist[i].loc.y()+k*xx[j];
                if (bomblist[i].loc.x()+k*yy[j] == x && bomblist[i].loc.y()+k*xx[j] == y)
                    return 0;
                if (h >= 0 && h < 15 && l >= 0 && l < 20 && (pic[h][l] == 1 || pic[h][l] == 2 || hitbomb))
                    break;
            }
        }
    }
    return 1;
}

void AIController::bfs(int x, int y, bool risk)
{
    int xx[5] = {0, 0, 0, 1, -1}; //坐标
    int yy[5] = {0, -1, 1, 0, 0}; //坐标
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 20; j++)
        {
            steps[i][j] = -1;
            pre[i][j] = QPointF(-1, -1);
        }
    steps[x][y] = 1;
    int front = 1, rear = 1;
    int p[505], q[505];
    p[1] = x, q[1] = y;
    while (front <= rear)
    {
        int step = steps[p[front]][q[front]];
        for (int i = 1; i <= 4; i++)
        {
            int h = p[front] + yy[i];
            int l = q[front] + xx[i];
            if (h >= 0 && h < 15 && l >= 0 && l < 20 && (pic[h][l] == 0 || pic[h][l] == 3)
                    && (risk || safe(h, l, step + 1) == 1))
            {
                if (steps[h][l] == -1 || step + 1 < steps[h][l])
                {
                    rear++;
                    p[rear] = h;
                    q[rear] = l;
                    steps[h][l] = step + 1;
                    pre[h][l] = QPointF(p[front], q[front]);
                }
            }
        }
        front++;
    }
}

bool AIController::move(int startx, int starty, int endx, int endy, float deltatime)
{
    if (steps[endx][endy] == -1)
        return false;
    if (startx == endx && starty == endy)
        return true;
    QStack<QPointF> path;
    QPointF curstep = QPointF(endx, endy);
    while (curstep != QPointF(startx, starty))
    {
        path.push(curstep);
        if (pre[(int)curstep.x()][(int)curstep.y()] == QPointF(-1, -1))
        {
            path.clear();
            return false;
        }
        else
            curstep = QPointF(pre[(int)curstep.x()][(int)curstep.y()]);
    }
    QPointF cur = QPointF(startx, starty);
    QPointF top = path.top();
    int dir;
    if (top.x() - cur.x() == -1 && top.y() == cur.y())
        dir = 1;
    else if (top.x() - cur.x() == 1 && top.y() == cur.y())
        dir = 2;
    else if (top.y() - cur.y() == -1 && top.x() == cur.x())
        dir = 3;
    else if (top.y() - cur.y() == 1 && top.x() == cur.x())
        dir = 4;
    else
        return false;
    if (moveable(deltatime))
        moveunit(dir);
    return true;
}

bool AIController::escape(int x, int y, float deltatime)
{
    observe();
    bfs(x, y, 1);
    int i, j;
    int minstep = 15 * 20 + 5;
    QPointF destin = QPointF(-1, -1);
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (steps[i][j] != -1 && steps[i][j] < minstep && safe(i, j, steps[i][j]) == 1)
            {
                minstep = steps[i][j];
                destin = QPointF(i, j);
            }
        }
    }
    //assert(destin != QPointF(-1, -1));
    if (destin == QPointF(-1, -1))
        return false;
    return move(x, y, destin.x(), destin.y(), deltatime);
}

void AIController::moveaway(int x, int y, float deltatime)  //可考虑更改bfs（冒险与否）
{
    int i, j;
    int mindelta = 20 + 5;
    QPointF closest = QPointF(-1, -1);
    for (i = 0; i < bomblist.size(); i++)
    {
        int h = bomblist[i].loc.x();
        int l = bomblist[i].loc.y();
        if (h == x && abs(l - y) < mindelta)
        {
            mindelta = abs(l - y);
            closest = QPointF(h, l);
        }
        else if (l == y && abs(h - x) < mindelta)
        {
            mindelta = abs(h - x);
            closest = QPointF(h, l);
        }
    }
    assert(closest != QPointF(-1, -1));
    if (closest.x() > x)
        moveunit(1);
    else if (closest.x() < x)
        moveunit(2);
    else if (closest.y() > y)
        moveunit(3);
    else if (closest.y() < y)
        moveunit(4);
    else
        randomwalk(deltatime);
}

bool AIController::picktools(int x, int y, float deltatime)
{
    int i, j;
    int minstep = 15 * 20 + 5;
    QPointF destin = QPointF(-1, -1);
    for (i = 0; i < toollist.size(); i++)
    {
        int h = toollist[i].loc.x();
        int l = toollist[i].loc.y();
        if (steps[h][l] != -1 && steps[h][l] < minstep)
        {
            minstep = steps[h][l];
            destin = QPointF(h, l);
        }
    }
    if (destin == QPointF(-1, -1))
        return false;
    return move(x, y, destin.x(), destin.y(), deltatime);
}

bool AIController::bombsoftwall(int x, int y, float deltatime)
{
    int i, j, k;
    int xx[5] = {0, 0, 0, 1, -1};
    int yy[5] = {0, -1, 1, 0, 0};
    int minstep = 15 * 20 + 5;
    QPointF destin = QPointF(-1, -1);
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (pic[i][j] == 1)
            {
                //assert(steps[i][j] == -1);
                for (k = 1; k <= 4; k++)
                {
                    int h = i + yy[k];
                    int l = j + xx[k];

                    if (h >= 0 && h < 15 && l >= 0 && l < 20 &&
                        steps[h][l] != -1 && steps[h][l] < minstep)
                    {
                        //moveunit(3);
                        minstep = steps[h][l];
                        destin = QPointF(h, l);
                        assert(minstep > 0);
                    }
                }
            }
        }
    }
    //assert(destin != QPointF(-1, -1));
    if (destin == QPointF(-1, -1))
        return false;
    //assert(move(x, y, destin.x(), destin.y(), deltatime));
    if (move(x, y, destin.x(), destin.y(), deltatime))
    {
        if (x == destin.x() && y == destin.y())
            setbomb(x, y);
        return true;
    }
    return false;
}

void AIController::setbomb(int x, int y)
{
    assert(curBombnum <= MostBombnum);
    if (this->curBombnum >= this->MostBombnum)
        return;
    this->curBombnum++;
    auto bomb = new GameObject();
    auto classification = new Bomb();
    QPointF pos = QPointF(40*y + 20, 40*x + 20);
    ImageTransformBuilder()
            .setPos(pos)
            .setImage(":/pictures/images/map/bomb.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(bomb);
    classification->setMaster(this);
    classification->setRange(this->BombRange);
    if (this->pushbomb)
        classification->setPushable();
    bomb->addComponent(classification);
    attachGameObject(bomb);
}

void AIController::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    health = this->gameObject->getComponent<Health>();
    assert(physics != nullptr);
    assert(imagetransform != nullptr);
    assert(health != nullptr);
    assert(gamemap != nullptr);
    assert(gamescene != nullptr);
    assert(player1 != nullptr && player2 != nullptr && player3 != nullptr);
    this->collider = imagetransform;
}

void AIController::onUpdate(float deltatime)
{
    checkcollide();
    if (!moveable(deltatime))
        return;
    //问题：1、短距离放炸弹死亡  2、推炸弹时不位于整格
    int i, j;
    QPointF curpos = this->imagetransform->pos();
    bool flag = false;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 20; j++)
        {
            int x = j * 40 + 20;
            int y = i * 40 + 15;
            if (curpos.x() - x >= -20 && curpos.x() - x < 20
               && curpos.y() - y >= -25 && curpos.y() - y < 15)
            {
                flag = true;
                break;
            }
        }
        if (flag)  break;
    }
    QPointF loc = QPointF(i, j);
    observe();
    bfs(loc.x(), loc.y(), 0);
    //assert(!picktools(loc.x(), loc.y(), deltatime));
    assert(safe(loc.x(), loc.y(), 0) != -1);
    if (safe(loc.x(), loc.y(), 0) == 0)
    {
        if (!escape(loc.x(), loc.y(), deltatime))
            moveaway(loc.x(), loc.y(), deltatime);
    }
    else if (!picktools(loc.x(), loc.y(), deltatime))
    {
        //assert(bomblist.empty());
        moveunit(0);
        //assert(bombsoftwall(loc.x(), loc.y(), deltatime));
        if (!bombsoftwall(loc.x(), loc.y(), deltatime))
            moveunit(0);
        //setbomb(loc.x(), loc.y());
        //moveunit(1);
        //else
            //moveunit(1);
    }
}
/*float vx = 0, vy = 0;
    srand((unsigned)time(NULL));
    if (moveable(deltatime))
        decision = rand() % 16 + 1; //123上 456下 789左 101112右 131415不动 16放炸弹
    switch (type)
    {
    case 1:
        if (decision == 1 || decision == 2 || decision == 3)
        {
            vy -= velocity;
            imagetransform->setImage(":/pictures/images/player/3-up.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-30)
                        && transform->pos().y() - imagetransform->pos().y() < 0)
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vy < 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(0, -240));
                    }
                    if (vy < 0)  vy = 0;
                }
            }
        }

        else if (decision == 4 || decision == 5 || decision == 6)
        {
            vy += velocity;
            imagetransform->setImage(":/pictures/images/player/3-down.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(44)
                        && transform->pos().y() - imagetransform->pos().y() > 15)
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vy > 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(0, 240));
                    }
                    if (vy > 0)  vy = 0;
                }
            }
        }
        else if (decision == 7 || decision == 8 || decision == 9)
        {
            vx -= velocity;
            imagetransform->setImage(":/pictures/images/player/3-left.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && imagetransform->pos().x() - transform->pos().x() < qreal(40)
                        && transform->pos().x() - imagetransform->pos().x() < qreal(-5)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vx < 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(-240, 0));
                    }
                    if (vx < 0)  vx = 0;
                }
            }
        }
        else if (decision == 10 || decision == 11 || decision == 12)
        {
            vx += velocity;
            imagetransform->setImage(":/pictures/images/player/3-right.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && transform->pos().x() - imagetransform->pos().x() < qreal(40)
                        && transform->pos().x() - imagetransform->pos().x() > qreal(5)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vx > 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(240, 0));
                    }
                    if (vx > 0)  vx = 0;
                }
            }
        }
        else if (decision == 16)
        {
            if (curBombnum >= MostBombnum)
                return;
            curBombnum++;
            auto bomb = new GameObject();
            auto classification = new Bomb();
            QPointF pos;
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    if (this->imagetransform->pos().x() - (j * 40 + 20) >= -20 &&
                            this->imagetransform->pos().x() - (j * 40 + 20) < 20 &&
                            this->imagetransform->pos().y() - (i * 40 + 20) >= -20 &&
                            this->imagetransform->pos().y() - (i * 40 + 20) < 20)
                    {
                        pos = QPointF(40 * j + 20, 40 * i + 20);
                        break;
                    }
                }
            }
            ImageTransformBuilder()
                    .setPos(pos)
                    .setImage(":/pictures/images/map/bomb.png")
                    .setAlignment(Qt::AlignCenter)
                    .addToGameObject(bomb);
            classification->setMaster(this);
            classification->setRange(this->BombRange);
            if (pushbomb)
                classification->setPushable();
            bomb->addComponent(classification);
            attachGameObject(bomb);
        }
        physics->setVelocity(vx, vy);
        break;

    case 2:
        decision = rand() % 16 + 1; //123上 456下 789左 101112右 131415不动 16放炸弹
        if (decision == 1 || decision == 2 || decision == 3)
        {
            vy -= velocity;
            imagetransform->setImage(":/pictures/images/player/4-up.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-30)
                        && transform->pos().y() - imagetransform->pos().y() < 0)
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vy < 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(0, -240));
                    }
                    if (vy < 0)  vy = 0;
                }
            }
        }

        else if (decision == 4 || decision == 5 || decision == 6)
        {
            vy += velocity;
            imagetransform->setImage(":/pictures/images/player/4-down.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(44)
                        && transform->pos().y() - imagetransform->pos().y() > 15)
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vy > 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(0, 240));
                    }
                    if (vy > 0)  vy = 0;
                }
            }
        }
        else if (decision == 7 || decision == 8 || decision == 9)
        {
            vx -= velocity;
            imagetransform->setImage(":/pictures/images/player/4-left.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && imagetransform->pos().x() - transform->pos().x() < qreal(40)
                        && transform->pos().x() - imagetransform->pos().x() < qreal(-5)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vx < 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(-240, 0));
                    }
                    if (vx < 0)  vx = 0;
                }
            }
        }
        else if (decision == 10 || decision == 11 || decision == 12)
        {
            vx += velocity;
            imagetransform->setImage(":/pictures/images/player/4-right.png");
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr && transform->pos().x() - imagetransform->pos().x() < qreal(40)
                        && transform->pos().x() - imagetransform->pos().x() > qreal(5)
                        && transform->pos().y() - imagetransform->pos().y() < qreal(40)
                        && transform->pos().y() - imagetransform->pos().y() > qreal(-20))
                {
                    auto object = transform->getParentGameObject();
                    auto wall = object->getComponent<Wall>();
                    auto bomb = object->getComponent<Bomb>();
                    if (wall == nullptr && bomb == nullptr)  continue;
                    if (bomb != nullptr && vx > 0 && pushbomb && bomb->getMaster() == this)
                    {
                        bomb->setVelocity(QPointF(240, 0));
                    }
                    if (vx > 0)  vx = 0;
                }
            }
        }
        else if (decision == 16)
        {
            if (curBombnum >= MostBombnum)
                return;
            curBombnum++;
            auto bomb = new GameObject();
            auto classification = new Bomb();
            QPointF pos;
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    if (this->imagetransform->pos().x() - (j * 40 + 20) >= -20 &&
                            this->imagetransform->pos().x() - (j * 40 + 20) < 20 &&
                            this->imagetransform->pos().y() - (i * 40 + 20) >= -20 &&
                            this->imagetransform->pos().y() - (i * 40 + 20) < 20)
                    {
                        pos = QPointF(40 * j + 20, 40 * i + 20);
                        break;
                    }
                }
            }
            ImageTransformBuilder()
                    .setPos(pos)
                    .setImage(":/pictures/images/map/bomb.png")
                    .setAlignment(Qt::AlignCenter)
                    .addToGameObject(bomb);
            classification->setMaster(this);
            classification->setRange(this->BombRange);
            if (pushbomb)
                classification->setPushable();
            bomb->addComponent(classification);
            attachGameObject(bomb);
        }
        physics->setVelocity(vx, vy);
        break;
    }*/

