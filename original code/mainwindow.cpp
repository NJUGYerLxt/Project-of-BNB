#include "mainwindow.h"
#include <QGraphicsEllipseItem>
#include <gameobject.h>
#include <imagetransform.h>
#include <shooter.h>
#include <summondummy.h>
#include <transformbuilder.h>
#include <physics.h>
#include <usercontroller.h>

#include "./ui_mainwindow.h"

void loadScene(GameScene *gameScene) {
    auto obj = new GameObject();
    auto transform = new Transform();
    auto circle = new QGraphicsEllipseItem (transform);  //画圆形图案
    circle->setRect(-5, -5, 100, 100);
    transform->setPos(100, 100);
    obj->addComponent(transform);
    obj->addComponent(new UserController());
    gameScene->attachGameObject(obj);
    auto physics = new Physics();
    physics->setVelocity(100, 0);
    obj->addComponent(physics);
    gameScene->attachGameObject(obj);
    auto shooter = new GameObject();
    ImageTransformBuilder()
        .setPos(QPointF(100, 100))
        .setImage("enemy_3_0.png")
        .setAlignment(Qt::AlignCenter)
        .addToGameObject(shooter);
    shooter->addComponent(new Shooter);
    gameScene->attachGameObject(shooter);

    auto summonDummyBtn = new GameObject();
    summonDummyBtn->addComponent(new Transform);
    summonDummyBtn->addComponent(new SummonDummy);
    gameScene->attachGameObject(summonDummyBtn);

    /*auto floor = new GameObject();
    auto pic = new ImageTransform();
    pic->setImage(":/floor/gamecode/map/floor.png");
    pic->setAlignment(Qt::AlignCenter);
    pic->setPos(QPointF(100, 100));
    pic->setImageRect(QRectF(-50, -50, 100, 100));
    floor->addComponent(pic);
    gameScene->attachGameObject(floor);*/
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  gameScene = new GameScene();
  gameScene->setParent(this);
  auto view = new QGraphicsView(gameScene, this);
  view->setFrameStyle(QFrame::NoFrame);
  view->resize(this->size());
  view->setSceneRect(QRect(0, 0, this->width(), this->height()));

  loadScene(gameScene);
}

MainWindow::~MainWindow() { delete ui; }
