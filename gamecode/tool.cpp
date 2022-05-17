#include "tool.h"
#include "playercontroller.h"

Tool::Tool(int type) {this->type = type; assert(type <= 4);}

void Tool::onAttach()
{
     imagetransform = this->gameObject->getComponent<ImageTransform>();
     assert(imagetransform != nullptr);
     this->collider = imagetransform;
     assert(collider != nullptr);
}

void Tool::onFirstUpdate()
{
    switch (type)  //1加速 2加范围 3炸弹数加一 4推炸弹
    {
    case 1:
        imagetransform->setImage(":/images/gamecode/map/SpeedTool.png");
        break;
    case 2:
        imagetransform->setImage(":/images/gamecode/map/RangeTool.png");
        break;
    case 3:
        imagetransform->setImage(":/images/gamecode/map/BombTool.png");
        break;
    case 4:
        imagetransform->setImage(":/images/gamecode/map/PushTool.png");
        break;
    }
}

void Tool::onUpdate(float deltatime)
{
    for (auto item : this->collider->collidingItems())
    {
        while (item->parentItem() != nullptr)
            item = item->parentItem();
        auto transform = dynamic_cast<Transform *>(item);
        if (transform == nullptr) continue;
        auto gameObject = transform->getParentGameObject();
        auto player = gameObject->getComponent<PlayerController>();
        if (player != nullptr && abs(transform->pos().x() - imagetransform->pos().x()) < qreal(30)
            && transform->pos().y() - imagetransform->pos().y() < qreal(44)
            && transform->pos().y() - imagetransform->pos().y() > qreal(-30))
        {
            switch (type)
            {
            case 1:
                player->ModifyVelocity();
                break;
            case 2:
                player->ModifyBombRange();
                break;
            case 3:
                player->ModifyMostBombNum();
                break;
            case 4:
                player->ModifyPushBomb();
                break;
            }
            destory(this->gameObject);
        }
    }
}
