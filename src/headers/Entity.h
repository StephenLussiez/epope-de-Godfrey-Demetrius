#include <string>
#include "Sprite.h"

class Entity
{
public:
    Entity(const ::std::string& name, float speed, const Sprite& sprite)
        : Name(name),
          speed(speed),
          sprite(sprite) {}

    void setName(std::string entityName);
    std::string getName();
    void setSpeed(float entitySpeed);
    float getSpeed();

private:
    std::string Name;
    float speed = 0;
    
    Sprite sprite;
};
