#include "bomb.h"
#include "light.h"
#include <QGraphicsRectItem>

Bomb::Bomb() {}

void Bomb::setMaster(PlayerController *master) {this->master = master;}

PlayerController *Bomb::getMaster() {return master;}

void Bomb::onAttach()
{
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    //detector = this->gameObject->getComponent<ImageTransform>();
    assert(imagetransform != nullptr);
    //detector->setImage(":/images/gamecode/map/transparentbomb.png");
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
        if (transform->pos().x() != imagetransform->pos().x() && transform->pos().y() != imagetransform->pos().y())  continue;
        hitable->beHit();
    }
    imagetransform->setImage(":/images/gamecode/map/bombing.png");
    cooldown -= deltatime;
    if (cooldown <= 0 && !Destoried)
    {
        destory(this->gameObject);
        Destoried = true;
    }
    if (Destoried || GenerateLight)  return;
    QPointF pos;
    for (int i = 1; i <= range; i++)
    {
        pos = QPointF(imagetransform->pos().x()-40*i, imagetransform->pos().y());
        auto light = new GameObject();
        auto component = new Light(this);
        component->setType(1);
        light->addComponent(component);
        ImageTransformBuilder()
            .setPos(pos)
            .setImage(":/images/gamecode/map/transparentlight.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(light);
        attachGameObject(light);
        if (component->gethit())  break;
    }
    for (int i = 1; i <= range; i++)
    {
        pos = QPointF(imagetransform->pos().x()+40*i, imagetransform->pos().y());
        auto light = new GameObject();
        auto component = new Light(this);
        component->setType(1);
        light->addComponent(component);
        ImageTransformBuilder()
            .setPos(pos)
            .setImage(":/images/gamecode/map/transparentlight.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(light);
        attachGameObject(light);
        if (component->gethit())  break;
    }
    for (int i = 1; i <= range; i++)
    {
        pos = QPointF(imagetransform->pos().x(), imagetransform->pos().y()-40*i);
        auto light = new GameObject();
        auto component = new Light(this);
        component->setType(2);
        light->addComponent(component);
        ImageTransformBuilder()
            .setPos(pos)
            .setImage(":/images/gamecode/map/transparentlight.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(light);
        attachGameObject(light);
        if (component->gethit())  break;
    }
    for (int i = 1; i <= range; i++)
    {
        pos = QPointF(imagetransform->pos().x(), imagetransform->pos().y()+40*i);
        auto light = new GameObject();
        auto component = new Light(this);
        component->setType(2);
        light->addComponent(component);
        ImageTransformBuilder()
            .setPos(pos)
            .setImage(":/images/gamecode/map/transparentlight.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(light);
        attachGameObject(light);
        if (component->gethit())  break;
    }
    GenerateLight = true;
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

void Bomb::Modifyrange()
{
    range++;
}

bool Bomb::getDestoried()
{
    return Destoried;
}
