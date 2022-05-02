#include "physics.h"
#include<QGraphicsEllipseItem>

//void loadScene(GameScene *scene)
//{
//    auto obj = new GameObject();
//    auto transform = new Transform();
//    auto circle = new QGraphicsEllipseItem (transform);
//    circle->setRect(-5, -5, 10, 10);
//    transform->setPos(100, 100);
//    obj->addComponent(transform);
//    scene->attachGameObject(obj);
//}

Physics::Physics()
{}

void Physics::onAttach()
{
    transform = this->gameObject->getComponent<Transform>();
    assert(transform != nullptr);
}

void Physics::onUpdate(float deltaTime)
{
    transform->moveBy(deltaTime * vx, deltaTime * vy);
}

void Physics::setVelocity(float vx, float vy)
{
    this->vx = vx;
    this->vy = vy;
}
