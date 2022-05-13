#include "bomb.h"

Bomb::Bomb()
{

}

void Bomb::setMaster(PlayerController *master) {this->master = master;}

PlayerController* Bomb::getMaster() {return master;}

void Bomb::explode(float deltatime)
{
    cooldown -= deltatime;
    if (cooldown <= 0)
        destory(this->gameObject);
}

void Bomb::onAttach()
{
    //bomb = this->gameObject;
    transform = this->gameObject->getComponent<Transform>();
    //assert(bomb != nullptr);
    assert(transform != nullptr);
    auto circle = new QGraphicsEllipseItem(this->transform);
    circle->setRect(QRectF(10, 10, 20, 20));  //（位置，大小）
    circle->setBrush(QBrush(Qt::black));
}

void Bomb::onUpdate(float deltatime)
{
    countdown -= deltatime;
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
