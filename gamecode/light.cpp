#include "light.h"
#include "health.h"

Light::Light(Bomb *bomb) {this->parentBomb = bomb;}

void Light::setCurRange(int range) {this->currange = range;}

void Light::setDirection(int direction)
{
    this->direction = direction;
    if (direction == 1 || direction == 2)
        type = 2;
    else if (direction == 3 || direction == 4)
        type = 1;
}

void Light::onAttach()
{
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    assert(imagetransform != nullptr);
    this->collider = imagetransform;
    assert(collider != nullptr);
}

void Light::onFirstUpdate()
{
    for (auto item : collider->collidingItems())
    {
        while (item->parentItem() != nullptr)
            item = item->parentItem();
        auto trans = dynamic_cast<Transform *>(item);
        if (trans == nullptr)  continue;
        auto gameObject = trans->getParentGameObject();
        auto hitable = gameObject->getComponent<Hitable>();
        if (hitable == nullptr
            && (gameObject->getComponent<Wall>() != nullptr
            || (gameObject != parentBomb->getParentGameObject() && gameObject->getComponent<Bomb>() != nullptr)))
        {
            hitwall = true;
            continue;
        }

        if (hitable != nullptr)
        {
            if (gameObject->getComponent<PlayerController>() == nullptr)
                hitable->beHit();
            else if (abs(trans->pos().x() - imagetransform->pos().x()) < qreal(40)
                     && trans->pos().y() - imagetransform->pos().y() < qreal(25)
                     && trans->pos().y() - imagetransform->pos().y() > qreal(-10))
            {
                hitable->beHit();
                auto master = parentBomb->getMaster();
                if (master != nullptr && gameObject->getComponent<PlayerController>() != master)
                    master->ModifyScore(hitplayer);
            }
            if (gameObject->getComponent<Wall>() != nullptr)
            {
                hitwall = true;
                gameObject->removeComponent(gameObject->getComponent<Wall>());
                gameObject->removeComponent(hitable);
                auto master = parentBomb->getMaster();
                if (master != nullptr)
                    master->ModifyScore(hitsoftwall);
            }
        }

        switch(type)
        {
        case 1:
            imagetransform->setImage(":/images/gamecode/map/horizontallight.png");
            break;
        case 2:
            imagetransform->setImage(":/images/gamecode/map/verticallight.png");
            break;
        }
        //attachGameObject(this->getParentGameObject());
    }
}

void Light::onUpdate(float deltatime)
{
    if (this->parentBomb->getDestoried())
    {
        destory(this->gameObject);
        return;
    }
    for (auto item : collider->collidingItems())
    {
        while (item->parentItem() != nullptr)
            item = item->parentItem();
        auto transform = dynamic_cast<Transform *>(item);
        if (transform == nullptr)  continue;
        auto gameObject = transform->getParentGameObject();
        auto hitable = gameObject->getComponent<Hitable>();
        if (hitable == nullptr
            && (gameObject->getComponent<Wall>() != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
            || (gameObject != parentBomb->getParentGameObject() && gameObject->getComponent<Bomb>() != nullptr)))
        {
            hitwall = true;
            continue;
        }
        if (hitable != nullptr)
        {
            if (gameObject->getComponent<PlayerController>() != nullptr
                    && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(40)
                    && transform->pos().y() - imagetransform->pos().y() < qreal(25)
                    && transform->pos().y() - imagetransform->pos().y() > qreal(-10))
            {
                hitable->beHit();
                auto master = parentBomb->getMaster();
                if (master != nullptr && gameObject->getComponent<PlayerController>() != master)
                    master->ModifyScore(hitplayer);
            }
        }
    }
    if (!hitwall && currange < parentBomb->getRange() && !generate)
    {
        QPointF pos;
        switch (direction)
        {
        case 1:
            pos = QPointF(imagetransform->pos().x(), imagetransform->pos().y()-40);
            break;
        case 2:
            pos = QPointF(imagetransform->pos().x(), imagetransform->pos().y()+40);
            break;
        case 3:
            pos = QPointF(imagetransform->pos().x()-40, imagetransform->pos().y());
            break;
        case 4:
            pos = QPointF(imagetransform->pos().x()+40, imagetransform->pos().y());
            break;
        }
        auto light = new GameObject();
        auto component = new Light(parentBomb);
        component->setDirection(direction);
        component->setCurRange(currange + 1);
        light->addComponent(component);
        ImageTransformBuilder()
                .setPos(pos)
                .setImage(":/images/gamecode/map/transparentlight.png")
                .setAlignment(Qt::AlignCenter)
                .addToGameObject(light);
        attachGameObject(light);
        generate = true;
    }
}

bool Light::gethitwall() {return hitwall;}
