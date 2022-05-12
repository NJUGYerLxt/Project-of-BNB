#include "gamemap.h"
#include <imagetransform.h>
#include <transformbuilder.h>

Gamemap::Gamemap()
{

}

void Gamemap::onAttach()
{
    int type;  //0地砖 1软墙 2硬墙
    int i, j;
    int content[15][20];
    for (i = 0; i <= 7; i++)
    {
        for (j = 0; j <= 9; j++)
        {
            if (i == 0 || j == 0)
                content[i][j] = 2;
            else if (i == 1 && (j == 1 || j == 2 || j == 3 || j == 4))
                content[i][j] = 0;
            else if (i == 2 && (j == 1 || j == 2))
                content[i][j] = 0;
            else
            {
                type = rand() % 10;
                if (type <= 3)
                    content[i][j] = 0;
                else if (type >= 4 && type <= 6)
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
}

void Gamemap::onUpdate(float deltatime)
{

}
