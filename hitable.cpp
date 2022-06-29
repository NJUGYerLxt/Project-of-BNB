#include "hitable.h"
#include "wall.h"
#include "tool.h"
#include "gamemap.h"

Hitable::Hitable() {}

void Hitable::setGameScene(GameScene *gameScene) {/*this->gameScene = gameScene;*/}

//void Hitable::ConnectGamemap(Gamemap *gamemap) {this->gamemap = gamemap;}

void Hitable::beHit()
{
    if (this->gameObject->getComponent<Wall>() != nullptr)
    {
        this->gameObject->getComponent<ImageTransform>()->setImage(":/pictures/images/map/floor.png");
        int generator = rand() % 10 + 1;
        if (generator <= 4)
        {
        auto tool = new GameObject();
        ImageTransformBuilder()
            .setPos(this->gameObject->getComponent<ImageTransform>()->pos())
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(tool);
        tool->addComponent(new Tool(generator));
        attachGameObject(tool);
        }
        //destory(this->gameObject);
    }
    else
      destory(this->gameObject);
}
