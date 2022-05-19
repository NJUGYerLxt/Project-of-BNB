#include "scoreboard.h"
#include "qfont.h"

ScoreBoard::ScoreBoard(PlayerController *player) {this->player = player;}

void ScoreBoard::onAttach()
{
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    assert(imagetransform != nullptr);
    assert(player != nullptr);
    text = new QGraphicsSimpleTextItem(imagetransform);
    text->setText("Score: " + score);
    text->setFont(QFont("微软雅黑", 12));
}

void ScoreBoard::onUpdate(float deltatime)
{
    //else
    score = QString::number(player->getScore());
    text->setText("Score: " + score);
    text->setFont(QFont("微软雅黑", 12));
}
