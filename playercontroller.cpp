#include "playercontroller.h"
#include "bomb.h"

PlayerController::PlayerController(int type) {this->type = type;}

QPointF PlayerController::getpos() {return this->imagetransform->pos();}

void PlayerController::ConnectGameScene(GameScene *gamescene) {this->gamescene = gamescene;}

void PlayerController::ConnectGamemap(Gamemap *gamemap) {this->gamemap = gamemap;}

void PlayerController::ModifyCurBombNum()
{
    assert(curBombnum > 0);
    curBombnum--;
}

void PlayerController::ModifyMostBombNum() {MostBombnum++;}

void PlayerController::ModifyBombRange() {BombRange++;}

void PlayerController::ModifyVelocity()
{
    if (velocity <= 240)
        velocity += 40;
    else
        velocity += 20;
}

void PlayerController::ModifyPushBomb() {pushbomb = true;}

void PlayerController::ModifyScore(int score) {this->score += score;}

int PlayerController::getScore() {return score;}

void PlayerController::Death() {dead = true;}

bool PlayerController::getdeath() {return dead;}

void PlayerController::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    assert(physics != nullptr);   
    assert(imagetransform != nullptr);
    this->collider = imagetransform;
}

void PlayerController::onUpdate(float deltatime)
{
    if (this->gameObject == nullptr || dead)  return;
    float vx = 0, vy = 0;
    switch (type)
    {
    case 1:
        if (getKey(Qt::Key_D))
        {
            vx += velocity;
            imagetransform->setImage(":/pictures/images/player/rightward.png");
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
        else if (getKey(Qt::Key_A))
        {
            vx -= velocity;
            imagetransform->setImage(":/pictures/images/player/leftward.png");
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
        else if (getKey(Qt::Key_W))
        {
            vy -= velocity;
            imagetransform->setImage(":/pictures/images/player/upward.png");
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
        else if (getKey(Qt::Key_S))
        {
            vy += velocity;
            imagetransform->setImage(":/pictures/images/player/downward.png");
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
        else if (getKeyDown(Qt::Key_Space))
        {
            //curinterval -= deltatime;
            if (curBombnum >= MostBombnum)
                return;
            //curinterval = interval;
            QPointF pos;
            QPointF loc;
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
                        //loc = QPointF(i, j);
                        break;
                    }
                }
            }
            /*auto attempt = new GameObject();
            auto type = new Bomb();
            ImageTransformBuilder()
                .setPos(pos)
                .setImage(":/pictures/images/map/transparentbomb.png")
                .setAlignment(Qt::AlignCenter)
                .addToGameObject(attempt);
            attempt->addComponent(type);
            attachGameObject(attempt);
            for (auto item : type->getcollider()->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform != nullptr)
                {
                    auto gameobject = transform->getParentGameObject();
                    auto bomb = gameobject->getComponent<Bomb>();
                    if (bomb != nullptr)
                    {
                        if (attempt != nullptr)
                            destory(attempt);
                        return;
                    }
                }
            }
            if (attempt != nullptr)
                destory(attempt);*/
            auto gameObjects = this->gamescene->getgameObjects();
            for (int i = 0; i < gameObjects.size(); i++)
            {
                if (gameObjects[i]->getComponent<Bomb>() != nullptr)
                {
                    auto curbomb = gameObjects[i]->getComponent<Bomb>();
                    if (curbomb->getpos() == pos)
                        return;
                }
            }
            curBombnum++;
            auto bomb = new GameObject();
            auto classification = new Bomb();
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
            //gamemap->InsertBomb(loc, BombRange, deltatime);
        }
        break;
    case 2:
        if (getKey(Qt::Key_Right))
        {
            vx += velocity;
            imagetransform->setImage(":/pictures/images/player/2-right.png");
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
        else if (getKey(Qt::Key_Left))
        {
            vx -= velocity;
            imagetransform->setImage(":/pictures/images/player/2-left.png");
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
        else if (getKey(Qt::Key_Up))
        {
            vy -= velocity;
            imagetransform->setImage(":/pictures/images/player/2-up.png");
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
        else if (getKey(Qt::Key_Down))
        {
            vy += velocity;
            imagetransform->setImage(":/pictures/images/player/2-down.png");
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
        else if (getKeyDown(Qt::Key_Return))
        {
            //curinterval -= deltatime;
            if (curBombnum >= MostBombnum)
                return;
            //curinterval = interval;
            QPointF pos;
            QPointF loc;
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
                        //loc = QPointF(i, j);
                        break;
                    }
                }
            }
            auto gameObjects = this->gamescene->getgameObjects();
            for (int i = 0; i < gameObjects.size(); i++)
            {
                if (gameObjects[i]->getComponent<Bomb>() != nullptr)
                {
                    auto curbomb = gameObjects[i]->getComponent<Bomb>();
                    if (curbomb->getpos() == pos)
                        return;
                }
            }
            curBombnum++;
            auto bomb = new GameObject();
            auto classification = new Bomb();
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
            //gamemap->InsertBomb(loc, BombRange, deltatime);
        }
        break;
    }
    physics->setVelocity(vx, vy);
}
