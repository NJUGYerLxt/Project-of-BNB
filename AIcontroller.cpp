#include "AIcontroller.h"
#include "tool.h"
#include "light.h"
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

QPointF AIController::CalPlayerLoc(QPointF pos)
{
    int i, j;
    bool flag = false;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 20; j++)
        {
            int x = j * 40 + 20;
            int y = i * 40 + 15;
            if (pos.x() - x >= -20 && pos.x() - x < 20
                    && pos.y() - y >= -25 && pos.y() - y < 15)
            {
                flag = true;
                break;
            }
        }
        if (flag)  break;
    }
    return QPointF(i, j);
}

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
                    if (bomb != nullptr && vy < 0 && pushbomb && bomb->getMaster() == this && bomb->getPushable())
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
                    if (bomb != nullptr && vy > 0 && pushbomb && bomb->getMaster() == this && bomb->getPushable())
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
                    if (bomb != nullptr && vx < 0 && pushbomb && bomb->getMaster() == this && bomb->getPushable())
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
                    if (bomb != nullptr && vx > 0 && pushbomb && bomb->getMaster() == this && bomb->getPushable())
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
                    if (bomb != nullptr && vy < 0 && pushbomb && bomb->getMaster() == this && bomb->getPushable())
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
                    if (bomb != nullptr && vy > 0 && pushbomb && bomb->getMaster() == this && bomb->getPushable())
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
                    if (bomb != nullptr && vx < 0 && pushbomb && bomb->getMaster() == this && bomb->getPushable())
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
                    if (bomb != nullptr && vx > 0 && pushbomb && bomb->getMaster() == this && bomb->getPushable())
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
    if (this->physics->getVelocity() == QPointF(0, 0))
        return true;
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
    lightlist.clear();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 20; j++)
            pic[i][j] = gamemap->getcontent(i, j);
    if (player1 != nullptr && !player1->getdeath())
    {
        pos = player1->getpos();
        for (i = 0; i < 15; i++)
            for (j = 0; j < 20; j++)
                if (pos.x() - (j * 40 + 20) >= -20 && pos.x() - (j * 40 + 20) < 20
                    && pos.y() - (i * 40 + 20) >= -20 && pos.y() - (i * 40 + 20) < 20)
                {
                    pic[i][j] = 3;
                    break;
                }
    }
    if (player2 != nullptr && !player2->getdeath())
    {
        pos = player2->getpos();
        for (i = 0; i < 15; i++)
            for (j = 0; j < 20; j++)
                if (pos.x() - (j * 40 + 20) >= -20 && pos.x() - (j * 40 + 20) < 20
                        && pos.y() - (i * 40 + 20) >= -20 && pos.y() - (i * 40 + 20) < 20)
                {
                    pic[i][j] = 3;
                    break;
                }
    }
    if (player3 != nullptr && !player3->getdeath())
    {
        pos = player3->getpos();
        for (i = 0; i < 15; i++)
            for (j = 0; j < 20; j++)
                if (pos.x() - (j * 40 + 20) >= -20 && pos.x() - (j * 40 + 20) < 20
                        && pos.y() - (i * 40 + 20) >= -20 && pos.y() - (i * 40 + 20) < 20)
                {
                    pic[i][j] = 3;
                    break;
                }
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
            newbomb.master = curbomb->getMaster()->gettype();
            newbomb.pushable = curbomb->getPushable();
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
        else if (gameObjects[i]->getComponent<Light>() != nullptr)
        {
            light newlight;
            auto curlight = gameObjects[i]->getComponent<Light>();
            newlight.loc = QPointF((curlight->getpos().y() - 20)/40,
                                   (curlight->getpos().x() - 20)/40);
            lightlist.append(newlight);
        }
    }
}

int AIController::safe(int x, int y, int step)
{
    if (x <= 0 || x >= 14 || y <= 0 || y >= 19)
        return -1;
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
        {
            if (bomblist[i].countdown <= safecountdown)
                return 2;
            else
                return 0;
        }
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
                {
                    if (bomblist[i].countdown <= safecountdown)
                        return 2;
                    else
                        return 0;
                }
                if (h >= 0 && h < 15 && l >= 0 && l < 20 && (pic[h][l] == 1 || pic[h][l] == 2 || hitbomb))
                    break;
            }
        }
    }
    for (i = 0; i < lightlist.size(); i++)
    {
        if (lightlist[i].loc.x() == x && lightlist[i].loc.y() == y)
            return 2;
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
                    && ((risk && safe(h, l, step + 1) != 2) || safe(h, l, step + 1) == 1))
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
    if (destin == QPointF(-1, -1))
        return false;
    return move(x, y, destin.x(), destin.y(), deltatime);
}

void AIController::moveaway(int x, int y, float deltatime)
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
    if (closest.x() > x && safe(x-1, y, 1) != 2 && safe(x-1, y, 1) != -1)
        moveunit(1);
    else if (closest.x() < x && safe(x+1, y, 1) != 2 && safe(x+1, y, 1) != -1)
        moveunit(2);
    else if (closest.y() > y && safe(x, y-1, 1) != 2 && safe(x, y-1, 1) != -1)
        moveunit(3);
    else if (closest.y() < y && safe(x, y+1, 1) != 2 && safe(x-1, y+1, 1) != -1)
        moveunit(4);
    else if (safe(x, y, 0) == 2)
        randomwalk(deltatime);
    else
        moveunit(0);
}

bool AIController::picktools(int x, int y, float deltatime, bool attack)
{
    int i, j, k;
    int minstep = 15 * 20 + 5;
    int xx[5] = {0, 0, 0, 1, -1};
    int yy[5] = {0, -1, 1, 0, 0};
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
    if (attack)
    {
        for (i = 0; i < 15; i++)
        {
            for (j = 0; j < 20; j++)
            {
                if (pic[i][j] == 3)
                {
                    for (k = 1; k <= 4; k++)
                    {
                        int h = i + yy[k];
                        int l = j + xx[k];
                        if (steps[h][l] != -1 && steps[h][l] < minstep)
                        {
                            minstep = steps[h][l];
                            destin = QPointF(h, l);
                        }
                    }
                }
            }
        }
    }
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
                for (k = 1; k <= 4; k++)
                {
                    int h = i + yy[k];
                    int l = j + xx[k];

                    if (h >= 0 && h < 15 && l >= 0 && l < 20 &&
                            steps[h][l] != -1 && steps[h][l] < minstep)
                    {
                        minstep = steps[h][l];
                        destin = QPointF(h, l);
                        assert(minstep > 0);
                    }
                }
            }
        }
    }
    if (destin == QPointF(-1, -1))
        return false;
    if (move(x, y, destin.x(), destin.y(), deltatime))
    {
        if (x == destin.x() && y == destin.y())
            setbomb(x, y);
        return true;
    }
    return false;
}

bool AIController::setbomb(int x, int y)
{
    assert(curBombnum <= MostBombnum);
    if (this->curBombnum >= this->MostBombnum)
        return false;
    for (int i = 0; i < bomblist.size(); i++)
    {
        if (bomblist[i].loc == QPointF(x, y))
            return false;
    }
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
    return true;
}

bool AIController::closeattack(int x, int y)
{
    QPointF loc[4];
    int i, j, k;
    for (i = 1; i <= 3; i++)
        loc[i] = QPointF(-1, -1);
    loc[0] = QPointF(x, y);
    QPointF pos;
    if (player1 != nullptr && !player1->getdeath())
    {
        pos = player1->getpos();
        loc[1] = CalPlayerLoc(pos);
    }
    if (player2 != nullptr && !player2->getdeath())
    {
        pos = player2->getpos();
        loc[2] = CalPlayerLoc(pos);
    }
    if (player3 != nullptr && !player3->getdeath())
    {
        pos = player3->getpos();
        loc[3] = CalPlayerLoc(pos);
    }
    bool flag;
    for (i = 1; i <= 3; i++)
    {
        flag = true;
        if (loc[i] == QPointF(-1, -1))
            continue;
        if (loc[i].x() == x && abs(loc[i].y() - y) <= this->BombRange)
        {
            for (j = fmin(loc[i].y(), y); j <= fmax(loc[i].y(), y); j++)
            {
                if (pic[x][j] == 1 || pic[x][j] == 2)
                {
                    flag = false;
                    break;
                }
                for (k = 0; k < bomblist.size(); k++)
                {
                    if (bomblist[k].loc == QPointF(x, j))
                    {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    break;
            }
            if (flag)
                return true;
        }
        else if (loc[i].y() == y && abs(loc[i].x() - x) <= this->BombRange)
        {
            for (j = fmin(loc[i].x(), x); j <= fmax(loc[i].x(), x); j++)
            {
                if (pic[j][y] == 1 || pic[j][y] == 2)
                {
                    flag = false;
                    break;
                }
                for (k = 0; k < bomblist.size(); k++)
                {
                    if (bomblist[k].loc == QPointF(j, y))
                    {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    break;
            }
            if (flag)
                return true;
        }
    }
    return false;
}

int AIController::farattack(int x, int y)
{
    if (!this->pushbomb)
        return 0;
    QPointF loc[4];
    int i, j, k;
    for (i = 1; i <= 3; i++)
        loc[i] = QPointF(-1, -1);
    loc[0] = QPointF(x, y);
    QPointF pos;
    if (player1 != nullptr && !player1->getdeath())
    {
        pos = player1->getpos();
        loc[1] = CalPlayerLoc(pos);
    }
    if (player2 != nullptr && !player2->getdeath())
    {
        pos = player2->getpos();
        loc[2] = CalPlayerLoc(pos);
    }
    if (player3 != nullptr && !player3->getdeath())
    {
        pos = player3->getpos();
        loc[3] = CalPlayerLoc(pos);
    }
    bool flag;
    for (i = 1; i <= 3; i++)
    {
        flag = true;
        if (loc[i] == QPointF(-1, -1))
            continue;
        if (loc[i].x() == x && abs(loc[i].y() - y) > this->BombRange)
        {
            for (j = fmin(loc[i].y(), y); j <= fmax(loc[i].y(), y); j++)
            {
                if (pic[x][j] == 1 || pic[x][j] == 2)
                {
                    flag = false;
                    break;
                }
                for (k = 0; k < bomblist.size(); k++)
                {
                    if (bomblist[k].loc == QPointF(x, j) && j != y)
                    {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    break;
            }
            if (flag)
            {
                if (loc[i].y() < y)
                    return 3;
                else
                    return 4;
            }
        }
        else if (loc[i].y() == y && abs(loc[i].x() - x) > this->BombRange)
        {
            for (j = fmin(loc[i].x(), x); j <= fmax(loc[i].x(), x); j++)
            {
                if (pic[j][y] == 1 || pic[j][y] == 2)
                {
                    flag = false;
                    break;
                }
                for (k = 0; k < bomblist.size(); k++)
                {
                    if (bomblist[k].loc == QPointF(j, y) && j != x)
                    {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    break;
            }
            if (flag)
            {
                if (loc[i].x() < x)
                    return 1;
                else
                    return 2;
            }
        }
    }
    return 0;
}

bool AIController::PushBomb(int x, int y, bool attack)
{
    if (!this->pushbomb)
        return false;
    int i, j;
    for (i = 0; i < bomblist.size(); i++)
    {
        if (bomblist[i].master == this->type && bomblist[i].pushable)
        {
            auto mybomb = bomblist[i];
            if (mybomb.loc.x() == x - 1 && mybomb.loc.y() == y)
            {
                if (farattack(x - 1, y) == 1 || !attack)
                {
                    moveunit(1);
                    return true;
                }
            }
            else if (mybomb.loc.x() == x + 1 && mybomb.loc.y() == y)
            {
                if (farattack(x + 1, y) == 2 || !attack)
                {
                    moveunit(2);
                    return true;
                }
            }
            else if (mybomb.loc.x() == x && mybomb.loc.y() == y - 1)
            {
                if (farattack(x, y - 1) == 3 || !attack)
                {
                    moveunit(3);
                    return true;
                }
            }
            else if (mybomb.loc.x() == x && mybomb.loc.y() == y + 1)
            {
                if (farattack(x, y + 1) == 4 || !attack)
                {
                    moveunit(4);
                    return true;
                }
            }
        }
    }
    return false;
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
    int i, j;
    QPointF curpos = this->imagetransform->pos();
    QPointF loc = CalPlayerLoc(curpos);
    observe();
    bfs(loc.x(), loc.y(), 0);
    bool res = PushBomb(loc.x(), loc.y(), 1);
    if (safe(loc.x(), loc.y(), 0) == 0 && !res)
    {
        if (!escape(loc.x(), loc.y(), deltatime))
        {
            if (!PushBomb(loc.x(), loc.y(), 0))
                moveaway(loc.x(), loc.y(), deltatime);
        }
    }
    else if (!this->pushbomb || this->velocity == 160)
    {
        if (closeattack(loc.x(), loc.y()))
            setbomb(loc.x(), loc.y());
        else if (!picktools(loc.x(), loc.y(), deltatime, 0))
        {
            moveunit(0);
            if (!bombsoftwall(loc.x(), loc.y(), deltatime))
                moveunit(0);
        }
    }
    else
    {
        if (closeattack(loc.x(), loc.y()))
            setbomb(loc.x(), loc.y());
        else
        {            
            if (!res)
            {
                int direction = farattack(loc.x(), loc.y());
                if (direction == 1 && safe(loc.x() + 1, loc.y(), 1) == 1)
                {
                    if (setbomb(loc.x(), loc.y()))
                        moveunit(2);
                }
                else if (direction == 2 && safe(loc.x() - 1, loc.y(), 1) == 1)
                {
                    if (setbomb(loc.x(), loc.y()))
                        moveunit(1);
                }
                else if (direction == 3 && safe(loc.x(), loc.y() + 1, 1) == 1)
                {
                    if (setbomb(loc.x(), loc.y()))
                        moveunit(4);
                }
                else if (direction == 4 && safe(loc.x(), loc.y() - 1, 1) == 1)
                {
                    if (setbomb(loc.x(), loc.y()))
                        moveunit(3);
                }
                else
                {
                    if (!picktools(loc.x(), loc.y(), deltatime, 1))
                    {
                        moveunit(0);
                        if (!bombsoftwall(loc.x(), loc.y(), deltatime))
                            moveunit(0);
                    }
                }
            }
        }
    }
}
