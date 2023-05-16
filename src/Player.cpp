#include "headers/Player.h"

void Player::setRouage()
{
    rouage = true;
}

void Player::setLife(int lifeNumber)
{
    life = lifeNumber;
}

void Player::deleteLife()
{
    life -= 1;
}

int Player::getLife()
{
    return life;
}

bool Player::getRouage()
{
    return rouage;
}

int Player::getShield()
{
    return shield;
}

void Player::addShield()
{
    shield += 1;
}
