export module Entity;

import <string>;

import DrawableSprite;

namespace EGD
{
    export class Entity
    {
    public:
        Entity(const ::std::string& name, float speed, const DrawableSprite& sprite)
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
        DrawableSprite sprite;
    };
}

module: private;

namespace EGD
{
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
}
