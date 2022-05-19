#include "mainwindow.h"
#include <QGraphicsEllipseItem>
#include "gameobject.h"
#include "imagetransform.h"
#include "transformbuilder.h"
#include "physics.h"
#include "playercontroller.h"
#include "gamemap.h"
#include "button.h"

#include "./ui_mainwindow.h"

void loadScene(GameScene *gameScene) {
    auto startingpage = new GameObject();
    ImageTransformBuilder()
         .setPos(QPointF(420, 330))
         .setImage(":/pictures/images/menu/Start.png")
         .setAlignment(Qt::AlignCenter)
         .addToGameObject(startingpage);
    gameScene->attachGameObject(startingpage);

    auto ButtonStart = new GameObject();
    auto button = new Button(gameScene);
    button->setType(1);
    ImageTransformBuilder()
         .setPos(QPointF(600, 240))
         .setImage(":/pictures/images/menu/ButtonStart.png")
         .setAlignment(Qt::AlignCenter)
         .addToGameObject(ButtonStart);
    ButtonStart->addComponent(button);
    gameScene->attachGameObject(ButtonStart);

    auto ButtonDesciption = new GameObject();
    auto description = new Button(gameScene);
    description->setType(2);
    ImageTransformBuilder()
         .setPos(QPointF(600, 350))
         .setImage(":/pictures/images/menu/ButtonDescription.png")
         .setAlignment(Qt::AlignCenter)
         .addToGameObject(ButtonDesciption);
    ButtonDesciption->addComponent(description);
    gameScene->attachGameObject(ButtonDesciption);

    auto ButtonExit = new GameObject();
    auto exit = new Button(gameScene);
    exit->setType(3);
    ImageTransformBuilder()
         .setPos(QPointF(600, 460))
         .setImage(":/pictures/images/menu/ButtonExit.png")
         .setAlignment(Qt::AlignCenter)
         .addToGameObject(ButtonExit);
    ButtonExit->addComponent(exit);
    gameScene->attachGameObject(ButtonExit);
    button->setMangement(description, 1);
    button->setMangement(exit, 2);
    button->setDetachPage(startingpage);
    button->setMainwindow(dynamic_cast<MainWindow *>(gameScene->parent()));    
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    gameScene = new GameScene();
    gameScene->setParent(this);
    this->setMinimumSize(800, 800);
    auto view = new QGraphicsView(gameScene, this);
    view->setFrameStyle(QFrame::NoFrame);
    view->resize(this->size());
    view->setSceneRect(QRect(0, 0, this->width(), this->height()));

    loadScene(gameScene);
}

MainWindow::~MainWindow() { delete ui; }
