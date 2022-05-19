#include "AIcontroller.h"

AIController::AIController(int type) : PlayerController(type) {this->type = type;}

void AIController::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    assert(physics != nullptr);
    assert(imagetransform != nullptr);
    this->collider = imagetransform;
}

void AIController::onUpdate(float deltatime)
{
    curtime -= deltatime;
    if (curtime > 0)
        return;
    float vx = 0, vy = 0;
    decision = rand() % 16 + 1; //123上 456下 789左 101112右 131415不动 16放炸弹
    srand((unsigned)time(NULL));
    switch (type)
    {
    case 1:
        if (decision == 1 || decision == 2 || decision == 3)
        {
            vy -= velocity;
            imagetransform->setImage(":/images/gamecode/player/3-up.png");
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
            imagetransform->setImage(":/images/gamecode/player/3-down.png");
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
            imagetransform->setImage(":/images/gamecode/player/3-left.png");
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
            imagetransform->setImage(":/images/gamecode/player/3-right.png");
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
                    .setImage(":/images/gamecode/map/bomb.png")
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
            imagetransform->setImage(":/images/gamecode/player/4-up.png");
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
            imagetransform->setImage(":/images/gamecode/player/4-down.png");
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
            imagetransform->setImage(":/images/gamecode/player/4-left.png");
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
            imagetransform->setImage(":/images/gamecode/player/4-right.png");
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
                    .setImage(":/images/gamecode/map/bomb.png")
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

