#include "button.h"
#include "stopbutton.h"
#include "scoreboard.h"

Button::Button(GameScene *gameScene) {this->gameScene = gameScene;}

void Button::setDetachPage(GameObject *page) {this->StartingPage = page;}

void Button::setMainwindow(MainWindow *mainwindow) {this->mainwindow = mainwindow;}

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
        auto controller1 = new PlayerController(1);
        ImageTransformBuilder()
            .setPos(QPointF(60, 55))
            .setImage(":/images/gamecode/player/downward.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(player1);
        player1->addComponent(controller1);
        player1->addComponent(physics1);
        player1->addComponent(new Health(1));
        gameScene->attachGameObject(player1);

        auto player2 = new GameObject();
        auto physics2 = new Physics();
        auto controller2 = new PlayerController(2);
        ImageTransformBuilder()
            .setPos(QPointF(740, 535))
            .setImage(":/images/gamecode/player/2-up.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(player2);
        player2->addComponent(controller2);
        player2->addComponent(physics2);
        player2->addComponent(new Health(1));
        gameScene->attachGameObject(player2);

        auto player3 = new GameObject();
        auto physics3 = new Physics();
        auto controller3 = new AIController(1);
        ImageTransformBuilder()
            .setPos(QPointF(740, 55))
            .setImage(":/images/gamecode/player/3-down.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(player3);
        player3->addComponent(controller3);
        player3->addComponent(physics3);
        player3->addComponent(new Health(1));
        gameScene->attachGameObject(player3);

        auto player4 = new GameObject();
        auto physics4 = new Physics();
        auto controller4 = new AIController(2);
        ImageTransformBuilder()
            .setPos(QPointF(60, 535))
            .setImage(":/images/gamecode/player/4-up.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(player4);
        player4->addComponent(controller4);
        player4->addComponent(physics4);
        player4->addComponent(new Health(1));
        gameScene->attachGameObject(player4);

        auto stopbutton = new GameObject();
        ImageTransformBuilder()
            .setPos(QPointF(50, 625))
            .setImage(":/images/gamecode/menu/StopButton.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(stopbutton);
        stopbutton->addComponent(new StopButton(gameScene));
        gameScene->attachGameObject(stopbutton);

        auto playerscore1 = new GameObject();
        ImageTransformBuilder()
            .setPos(QPointF(135, 625))
            .setImage(":/images/gamecode/menu/1-Score.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(playerscore1);
        gameScene->attachGameObject(playerscore1);
        auto scoreboard1 = new GameObject();
        auto board1 = new ScoreBoard(controller1);
        ImageTransformBuilder()
            .setPos(QPointF(170, 615))
            .setImage(":/images/gamecode/menu/ScoreBoard.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(scoreboard1);
        scoreboard1->addComponent(board1);
        gameScene->attachGameObject(scoreboard1);

        auto playerscore2 = new GameObject();
        ImageTransformBuilder()
            .setPos(QPointF(300, 625))
            .setImage(":/images/gamecode/menu/2-Score.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(playerscore2);
        gameScene->attachGameObject(playerscore2);
        auto scoreboard2 = new GameObject();
        auto board2 = new ScoreBoard(controller2);
        ImageTransformBuilder()
            .setPos(QPointF(335, 615))
            .setImage(":/images/gamecode/menu/ScoreBoard.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(scoreboard2);
        scoreboard2->addComponent(board2);
        gameScene->attachGameObject(scoreboard2);

        auto playerscore3 = new GameObject();
        ImageTransformBuilder()
            .setPos(QPointF(465, 625))
            .setImage(":/images/gamecode/menu/3-Score.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(playerscore3);
        gameScene->attachGameObject(playerscore3);
        auto scoreboard3 = new GameObject();
        auto board3 = new ScoreBoard(controller3);
        ImageTransformBuilder()
            .setPos(QPointF(500, 615))
            .setImage(":/images/gamecode/menu/ScoreBoard.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(scoreboard3);
        scoreboard3->addComponent(board3);
        gameScene->attachGameObject(scoreboard3);

        auto playerscore4 = new GameObject();
        ImageTransformBuilder()
            .setPos(QPointF(635, 625))
            .setImage(":/images/gamecode/menu/4-Score.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(playerscore4);
        gameScene->attachGameObject(playerscore4);
        auto scoreboard4 = new GameObject();
        auto board4 = new ScoreBoard(controller4);
        ImageTransformBuilder()
            .setPos(QPointF(670, 615))
            .setImage(":/images/gamecode/menu/ScoreBoard.png")
            .setAlignment(Qt::AlignCenter)
            .addToGameObject(scoreboard4);
        scoreboard4->addComponent(board4);
        gameScene->attachGameObject(scoreboard4);

        detachGameObject(this->gameObject);
    }
    else if (type == 2)
    {
        if (!clicked)
        {
            auto des = new GameObject();
            ImageTransformBuilder()
                .setPos(QPointF(260, 300))
                .setImage(":/images/gamecode/menu/Description.png")
                .setAlignment(Qt::AlignCenter)
                .addToGameObject(des);
            Des = des;
            gameScene->attachGameObject(des);
            clicked = true;
        }
        else
        {
            detachGameObject(Des);
            clicked = false;
        }
    }
    else if (type == 3)
        mainwindow->close();
}
