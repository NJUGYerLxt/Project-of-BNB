#ifndef BUTTON_H
#define BUTTON_H

#include "component.h"
#include "gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include "physics.h"
#include "hitable.h"
#include "health.h"
#include "wall.h"
#include "playercontroller.h"
#include "AIcontroller.h"
#include "gamemap.h"
#include "mainwindow.h"

class Button: public Component
{
public:
    Button(GameScene *gameScene);
    void setMangement(Button *button, int type); //1为说明 2为退出
    void setDetachPage(GameObject *page);
    void setMainwindow(MainWindow *mainwindow);
    void onClick(QGraphicsSceneMouseEvent *ev) override;
    void onAttach() override;
    void onUpdate(float deltatime) override;
    void setType(int type);

protected:
    int type;
    ImageTransform* imagetransform = nullptr;
    Button *description;
    Button *exit;
    GameScene *gameScene;
    GameObject *StartingPage = nullptr;
    GameObject *Des = nullptr;
    MainWindow *mainwindow;
    bool attached = false;
    bool clicked = false;
};

#endif // BUTTON_H
