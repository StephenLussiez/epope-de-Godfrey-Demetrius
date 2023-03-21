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

        void setName();
        void getName();
        void setSpeed();
        void getSpeed();

    private:
        std::string Name;
        float speed = 0;
        DrawableSprite sprite;
    };
}
