#include "button.h"

Button::Button(GameScene *gameScene) {this->gameScene = gameScene;}

void Button::setDetachPage(GameObject *page) {this->StartingPage = page;}

void Button::setMangement(Button *button, int type)
{
    switch(type)
    {
    case 1:
        description = button;
        break;
    case 2:
        exit = button;
        break;
    }
}

void Button::setType(int type) {this->type = type;}

void Button::onAttach()
{
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    assert(imagetransform != nullptr);
    // Handle mouse event of text by this->transform
    imagetransform->setFiltersChildEvents(true);
}

void Button::onUpdate(float deltatime) {}

void Button::onClick(QGraphicsSceneMouseEvent *ev)
{
    if (type == 1)
    {
        if (description->gameObject != nullptr)
            description->detachGameObject(description->gameObject);
        if (exit->gameObject != nullptr)
            exit->detachGameObject(exit->gameObject);
        if (StartingPage != nullptr)
            detachGameObject(StartingPage);
        new Gamemap(this->gameScene);
        auto player1 = new GameObject();
        auto physics1 = new Physics();
        ImageTransformBuilder()
            .setPos(QPointF(60, 55))
            .setImage(":/images/gamecode/player/downward.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(player1);
        player1->addComponent(new PlayerController(1));
        player1->addComponent(physics1);
        player1->addComponent(new Health(1));
        gameScene->attachGameObject(player1);

        auto player2 = new GameObject();
        auto physics2 = new Physics();
        auto transform2 = new Transform();
        auto image2 = new QGraphicsEllipseItem (transform2);
        image2->setRect(100, 100, 100, 100);
        transform2->setPos(250, 250);
        player2->addComponent(transform2);
        player2->addComponent(new PlayerController(2));
        player2->addComponent(physics2);
        //gameScene->attachGameObject(player2);
        detachGameObject(this->gameObject);
    }
    //else if (type == 2)
}
