#pragma once

#include "Entity.h"

class Player final : public Entity
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
#pragma once
