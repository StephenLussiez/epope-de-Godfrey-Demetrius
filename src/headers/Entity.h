#include <string>
#include "Sprite.h"

class Entity
{
public:

    Entity(::std::string name, float speed, sf::Sprite sprite)
        : Name(std::move(name)),
          speed(speed),
          sprite(std::move(sprite)) {}

    void setName(std::string entityName);
    std::string getName();
    void setSpeed(float entitySpeed);
    float getSpeed();

private:
    std::string Name;
    float speed = 0;
    sf::Sprite sprite;
};
