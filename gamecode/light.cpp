#include "light.h"
#include "health.h"

Light::Light(Bomb *parentBomb) {this->parentBomb = parentBomb;}

void Light::setType(int type) {this->type = type;}

void Light::onAttach()
{
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    this->collider = imagetransform;
    assert(collider != nullptr);
    if (!attached)
    {
        for (auto item : collider->collidingItems())
        {
            while (item->parentItem() != nullptr)
                item = item->parentItem();
            auto trans = dynamic_cast<Transform *>(item);
            if (trans == nullptr)  continue;
            auto gameObject = trans->getParentGameObject();
            auto hitable = gameObject->getComponent<Hitable>();
            if (hitable == nullptr && gameObject->getComponent<Wall>() != nullptr)  continue;
            if (hitable != nullptr)
            {
                hitable->beHit();
                hit = true;
                if (gameObject->getComponent<Health>() == nullptr)
                    gameObject->removeComponent(gameObject->getComponent<Hitable>());
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
            attachGameObject(this->getParentGameObject());
        }
        attached = true;
    }
}

void Light::onUpdate(float deltatime)
{

    if (this->parentBomb->getDestoried())
        destory(this->gameObject);
}

bool Light::gethit() {return hit;}
