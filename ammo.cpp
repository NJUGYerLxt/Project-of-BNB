#include "ammo.h"

#include <QBrush>
#include <QGraphicsEllipseItem>

#include "gamecode/hitable.h"

Ammo::Ammo(QPointF velocity) : Component(), velocity(velocity) {}

void Ammo::onAttach() {
  this->transform = this->gameObject->getComponent<Transform>(); //transform 指针指向Transform类组件
  Q_ASSERT(this->transform != nullptr);
  auto circle = new QGraphicsEllipseItem(this->transform);
  circle->setRect(QRectF(-10, -10, 20, 20));  //（位置，大小）
  circle->setBrush(QBrush(Qt::black));
  this->collider = circle;  //绑定，后检测与circle的碰撞
}

void Ammo::onUpdate(float deltaTime) {
  timeToLive -= deltaTime;
  if (timeToLive < 0) {
    destory(this->gameObject);
  }

  this->transform->setPos(this->transform->pos() + velocity * deltaTime);
  for (auto item : this->collider->collidingItems()) {
    while (item->parentItem() != nullptr)  //item相当于碰撞时相交的部分
        item = item->parentItem();  //取出碰撞对象
    auto transform = dynamic_cast<Transform *>(item);
    if (transform == nullptr) continue;
    auto gameObject = transform->getParentGameObject();
    auto hitable = gameObject->getComponent<Hitable>(); //getComponent<T>表示找到属于T类的组件
    if (hitable == nullptr) continue;
    hitable->beHit();
    destory(this->gameObject);
    break;
  }
}
