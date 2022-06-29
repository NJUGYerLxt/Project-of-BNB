#include "AIcontroller.h"
#include "tool.h"

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

bool AIController::moveunit()
{
    QPointF curpos = imagetransform->pos();
    bool flag = false;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            int x = j * 40 + 20;
            int y = i * 40 + 15;
            if (abs(curpos.x() - x) <= 5 && abs(curpos.y() - y) <= 8)
            {
                flag = true;
                break;
            }
        }
        if (flag)  break;
    }
   return flag;
}

void AIController::observe()
{
    int i, j;
    QPointF pos;
    QList <GameObject *> gameObjects;
    bomblist.clear();
    toollist.clear();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 15; j++)
            pic[i][j] = gamemap->getcontent(i, j);
    pos = player1->getpos();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 15; j++)
            if (pos.x() - (j * 40 + 20) >= -20 && pos.x() - (j * 40 + 20) < 20
             && pos.y() - (i * 40 + 20) >= -20 && pos.y() - (i * 40 + 20) < 20)
            {
                pic[i][j] = 3;
                break;
            }

    pos = player2->getpos();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 15; j++)
            if (pos.x() - (j * 40 + 20) >= -20 && pos.x() - (j * 40 + 20) < 20
             && pos.y() - (i * 40 + 20) >= -20 && pos.y() - (i * 40 + 20) < 20)
            {
                pic[i][j] = 3;
                break;
            }

    pos = player3->getpos();
    for (i = 0; i < 15; i++)
        for (j = 0; j < 15; j++)
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
            newbomb.loc = QPointF((curbomb->getpos().y() + 20)/40 - 1,
                                  (curbomb->getpos().x() + 20)/40 - 1);
            newbomb.range = curbomb->getRange();
            newbomb.countdown = curbomb->getCountdown();
        }
        else if (gameObjects[i]->getComponent<Tool>() != nullptr)
        {
            tool newtool;
            auto curtool = gameObjects[i]->getComponent<Tool>();
            newtool.loc = QPointF((curtool->getpos().y() + 20)/40 - 1,
                                  (curtool->getpos().x() + 20)/40 - 1);
            newtool.type = curtool->getType();
        }
    }
}

//void AIController::InsertBomb(Bomb *bomb) {bomblist.append(bomb);}

//void AIController::RemoveBomb(Bomb *bomb) {bomblist.removeOne(bomb);}

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
    if (health->gethealth() <= 0)
    {
        physics->setVelocity(0, 0);
        imagetransform->setImage(":/pictures/images/player/death.png");
        return;
    }
    float vx = 0, vy = 0;
    srand((unsigned)time(NULL));
    if (moveunit())
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
        /*else if (decision == 16)
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
        }*/
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
    }
}

