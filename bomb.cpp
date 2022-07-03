#include "bomb.h"
#include "light.h"
#include <QGraphicsRectItem>

Bomb::Bomb() {}

void Bomb::setMaster(PlayerController *master) {this->master = master;}

void Bomb::setRange(int range) {this->range = range;}

void Bomb::setPushable() {pushable = true;}

void Bomb::setVelocity(QPointF velocity) {this->velocity = velocity;}

PlayerController *Bomb::getMaster() {return master;}

int Bomb::getRange() {return range;}

bool Bomb::getDestoried() {return Destoried;}

QPointF Bomb::getpos() {return this->imagetransform->pos();}

float Bomb::getCountdown() {return countdown;}

bool Bomb::getPushable() {return this->pushable;}

void Bomb::onAttach()
{
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    assert(imagetransform != nullptr);
    this->collider = imagetransform;
}

void Bomb::explode(float deltatime)
{

    for (auto item : this->collider->collidingItems())
    {
        while (item->parentItem() != nullptr)
            item = item->parentItem();
        auto transform = dynamic_cast<Transform *>(item);
        if (transform == nullptr)  continue;
        auto gameObject = transform->getParentGameObject();
        auto hitable = gameObject->getComponent<Hitable>();
        if (hitable == nullptr)  continue;
        if (abs(transform->pos().x() - imagetransform->pos().x()) >= qreal(15)
            && abs(transform->pos().y() - imagetransform->pos().y()) >= qreal(15))
            continue;
        hitable->beHit();
        if (gameObject->getComponent<Wall>() != nullptr)
        {
            gameObject->removeComponent(gameObject->getComponent<Wall>());
            gameObject->removeComponent(hitable);
        }
        if (gameObject->getComponent<PlayerController>() != nullptr
            && !gameObject->getComponent<PlayerController>()->getdeath()
            && gameObject->getComponent<PlayerController>() != this->master)
        {
            assert(master != nullptr);
            master->ModifyScore(hitplayer);
        }
    }
    imagetransform->setImage(":/pictures/images/map/bombing.png");
    cooldown -= deltatime;
    if (cooldown <= 0 && !Destoried)
    {
        destory(this->gameObject);
        Destoried = true;
    }
    if (Destoried || GenerateLight)  return;

    QPointF pos;
    //左光束
    pos = QPointF(imagetransform->pos().x()-40, imagetransform->pos().y());
    auto lightleft = new GameObject();
    auto componentleft = new Light(this);
    componentleft->setCurRange(1);
    componentleft->setDirection(3);
    lightleft->addComponent(componentleft);
    ImageTransformBuilder()
        .setPos(pos)
        .setImage(":/pictures/images/map/transparentlight.png")
        .setAlignment(Qt::AlignCenter)
        .addToGameObject(lightleft);
    attachGameObject(lightleft);
    //右光束
    pos = QPointF(imagetransform->pos().x()+40, imagetransform->pos().y());
    auto lightright = new GameObject();
    auto componentright = new Light(this);
    componentright->setCurRange(1);
    componentright->setDirection(4);
    lightright->addComponent(componentright);
    ImageTransformBuilder()
        .setPos(pos)
        .setImage(":/pictures/images/map/transparentlight.png")
        .setAlignment(Qt::AlignCenter)
        .addToGameObject(lightright);
    attachGameObject(lightright);
    //上光束
    pos = QPointF(imagetransform->pos().x(), imagetransform->pos().y()-40);
    auto lightup = new GameObject();
    auto componentup = new Light(this);
    componentup->setCurRange(1);
    componentup->setDirection(1);
    lightup->addComponent(componentup);
    ImageTransformBuilder()
        .setPos(pos)
        .setImage(":/pictures/images/map/transparentlight.png")
        .setAlignment(Qt::AlignCenter)
        .addToGameObject(lightup);
    attachGameObject(lightup);
    //下光束
    pos = QPointF(imagetransform->pos().x(), imagetransform->pos().y()+40);
    auto lightdown = new GameObject();
    auto componentdown = new Light(this);
    componentdown->setCurRange(1);
    componentdown->setDirection(2);
    lightdown->addComponent(componentdown);
    ImageTransformBuilder()
        .setPos(pos)
        .setImage(":/pictures/images/map/transparentlight.png")
        .setAlignment(Qt::AlignCenter)
        .addToGameObject(lightdown);
    attachGameObject(lightdown);

    GenerateLight = true;
}

void Bomb::onUpdate(float deltatime)
{
    countdown -= deltatime;
    change -= deltatime;
    if (change <= 0)
    {
        change = changetime;
        switch(condition)
        {
        case 0:
            imagetransform->setImage(":/pictures/images/map/bomb-2.png");
            break;
        case 1:
            imagetransform->setImage(":/pictures/images/map/bomb.png");
            break;
        }
        condition = 1 - condition;
    }
    //if (!pushable)
        //velocity = QPointF(0, 0);
    imagetransform->setPos(imagetransform->pos() + velocity * deltatime);
    if (velocity != QPointF(0, 0))
    {
        countdown = bombtime;
        pushable = false;
        for (auto item : this->collider->collidingItems())
        {
            while (item->parentItem() != nullptr)
                item = item->parentItem();
            auto transform = dynamic_cast<Transform *>(item);
            if (transform == nullptr)  continue;
            auto gameObject = transform->getParentGameObject();
            auto wall = gameObject->getComponent<Wall>();
            auto player = gameObject->getComponent<PlayerController>();
            auto bomb = gameObject->getComponent<Bomb>();
            if (wall != nullptr || (player != nullptr && player != master) || bomb != nullptr)
            {
                velocity = QPointF(0, 0);
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
                imagetransform->setPos(pos);
            }
        }
    }
    if (countdown <= 0)
    {
        if (!ChangeCondition)
        {
            master->ModifyCurBombNum();
            ChangeCondition = true;
        }
        explode(deltatime);
    }
}

QGraphicsItem *Bomb::getcollider() {return collider;}
