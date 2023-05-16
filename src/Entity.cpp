#include "headers/Entity.h"


void Entity::setName(std::string entityName)
{
    Name = entityName;
}

std::string Entity::getName()
{
    return Name;
}

void Entity::setSpeed(float entitySpeed)
{
    speed = entitySpeed;
}

float Entity::getSpeed()
{
    return speed;
}
