#include <SFML/Graphics.hpp>

class GameEngine
{
public:
    GameEngine();
    int Gameloop();
    void GameInputs(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Time deltaTime,
                    sf::Sprite& plateformSprite1, float parallaxOffset);
    void GameDrawing(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Sprite& carte1Sprite,
                     sf::Sprite& carte2Sprite, sf::Sprite& plateforme1Sprite, float parallaxOffset);
    bool CheckCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
    void GamePhysics(sf::Sprite& playerSprite, sf::Time deltaTime, sf::Sprite& plateformSprite1);
};
