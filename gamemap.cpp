#include "gamemap.h"
#include "imagetransform.h"
#include "transformbuilder.h"
#include "tool.h"

Gamemap::Gamemap(GameScene *gameScene)
{
    int type;
    int i, j;
    int content[15][20]; //0地砖 1软墙 2硬墙
    srand((unsigned)time(NULL));
    for (i = 0; i <= 7; i++)
    {
        for (j = 0; j <= 9; j++)
        {
            if (i == 0 || j == 0)
                content[i][j] = 2;
            else if (i == 1 && (j == 1 || j == 2 || j == 3))
                content[i][j] = 0;
            else if ((i == 2 || i == 3) && j == 1)
                content[i][j] = 0;
            else
            {
                type = rand() % 10;
                if (type <= 1)
                    content[i][j] = 0;
                else if (type >= 2 && type <= 6)
                    content[i][j] = 1;
                else
                    content[i][j] = 2;
            }
        }
    }
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (i <= 7 && j <= 9)
                continue;
            content[i][j] = content[i >= 8 ? 14-i : i][j >= 10 ? 19-j : j];
        }
    }
    //挂图像
    int generator;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 20; j++)
        {
            block[i][j] = new GameObject();
            switch (content[i][j])
            {
            case 0:
                ImageTransformBuilder()
                    .setPos(QPointF(40*j+20, 40*i+20))
                    .setImage(":/pictures/images/map/floor.png")
                    .setAlignment(Qt::AlignCenter)
                    .addToGameObject(block[i][j]);
                break;
            case 1:
                ImageTransformBuilder()
                    .setPos(QPointF(40*j+20, 40*i+20))
                    .setImage(":/pictures/images/map/softwall.png")
                    .setAlignment(Qt::AlignCenter)
                    .addToGameObject(block[i][j]);
                //hitable->setGameScene(gameScene);
                block[i][j]->addComponent(new Hitable());
                block[i][j]->addComponent(new Wall());
                break;
            case 2:
                ImageTransformBuilder()
                    .setPos(QPointF(40*j+20, 40*i+20))
                    .setImage(":/pictures/images/map/hardwall.png")
                    .setAlignment(Qt::AlignCenter)
                    .addToGameObject(block[i][j]);
                //block[i][j]->addComponent(new Health(-1));
                block[i][j]->addComponent(new Wall());
                break;
            }
            location[i][j] = QPointF(40*j+20, 40*i+20);
            gameScene->attachGameObject(block[i][j]);
        }
    }
}

GameObject* Gamemap::getblock(int i, int j)
{
    return block[i][j];
}

QPointF Gamemap::getblocklocation(int i, int j)
{
    return location[i][j];
}
