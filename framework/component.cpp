#include "component.h"
#include "gameobject.h"

Component::Component() : QObject() {}  //建立该类对象

void Component::attachGameObject(GameObject *gameObject) {
  this->gameObject->attachGameObject(gameObject); // 将 gameObject 挂载到 GameScene 上
}
void Component::detachGameObject(GameObject *gameObject) {
  this->gameObject->detachGameObject(gameObject); // 将 gameObject 从 GameScene 中移除
}
void Component::destory(GameObject *gameObject) {
  this->gameObject->destory(gameObject); // 将 gameObject 从 GameScene 中移除并销毁（delete）
}

bool Component::getKey(Qt::Key key) { return this->gameObject->getKey(key); }
bool Component::getKeyDown(Qt::Key key) {
  return this->gameObject->getKeyDown(key);
}
bool Component::getKeyUp(Qt::Key key) {
  return this->gameObject->getKeyUp(key);
}

GameObject *Component::getParentGameObject() { return this->gameObject; } //返回指向的 gameObject（父对象）
void Component::setParentGameObject(GameObject *gameObject) {
  this->setParent(gameObject);
  this->gameObject = gameObject; //将 gameObject 设为父对象并将指针指向它
}
