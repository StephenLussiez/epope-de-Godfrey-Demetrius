export module Player;

import <string>;

import <SFML/Graphics/Drawable.hpp>;

import Entity;


namespace EGD
{
    export class Player final : public Entity
    {
    public:
        void setRouage();
        bool getRouage();
        void addShield();
        int getShield();
        void setLife(int lifeNumber);
        int getLife();
        void deleteLife();

    private:
        int life;
        bool rouage;
        int shield;
    };
}

module: private;

namespace EGD
{
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
}
