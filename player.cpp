#include "player.h"


Player::Player()
{
    mColor = Qt::black;
}

Player::Player(const Qt::GlobalColor& color)
{
    mColor = color;
    score = 0;
}

QColor Player::getColor() const
{
    return mColor;
}

int Player::getScore() const
{
    return score;
}

void Player::resetScore()
{
    score = 0;
}

void Player::win()
{
    score += 1;
}
