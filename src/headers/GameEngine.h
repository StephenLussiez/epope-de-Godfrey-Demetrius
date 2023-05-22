#include <SFML/Graphics.hpp>

class GameEngine
{
public:
    GameEngine();
    int Gameloop();
    void GameInputs(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Time& deltaTime, float& limitTimeJump,
                    bool& canPressLeft, bool& canPressRight,
                    float& parallaxOffset);
    void GameDrawing(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Sprite& carte1Sprite,
                     sf::Sprite& carte2Sprite, sf::Sprite& carte3Sprite,
                     sf::Sprite& carte4Sprite, sf::Sprite& carte5Sprite,
                     sf::Sprite& carte6Sprite, sf::Sprite& carte7Sprite,
                     sf::Sprite& carte8Sprite, sf::Sprite& carte9Sprite,
                     sf::Sprite& carte10Sprite, sf::Sprite& plateforme1Sprite, sf::Sprite& plateforme2Sprite,
                     sf::Sprite& plateforme3Sprite, sf::Sprite& plateforme4Sprite,
                     sf::Sprite& plateforme5Sprite, sf::Sprite& plateforme6Sprite,
                     sf::Sprite& plateforme7Sprite, sf::Sprite& plateforme8Sprite,
                     sf::Sprite& plateforme9Sprite, sf::Sprite& plateforme10Sprite, sf::Sprite& obstacle1Sprite,
                     sf::Sprite& obstacle2Sprite, sf::Sprite& enemy1Sprite, sf::Sprite& enemy2Sprite,
                     sf::Sprite& enemy3Sprite,
                     sf::Sprite& finishSprite,
                     float& parallaxOffset);
    bool CheckCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
    bool IsPlayerAboveEnemy(const sf::Sprite& playerSprite, const sf::Sprite& enemySprite);
    bool IsPlayerOnTheRight(const sf::Sprite& playerSprite, const sf::Sprite& sprite);
    bool IsPlayerOnTheLeft(const sf::Sprite& playerSprite, const sf::Sprite& sprite);
    void GamePhysics(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Time deltaTime,
                     sf::Sprite& plateformSprite1,
                     sf::Sprite& plateforme2Sprite,
                     sf::Sprite& plateforme3Sprite, sf::Sprite& plateforme4Sprite,
                     sf::Sprite& plateforme5Sprite, sf::Sprite& plateforme6Sprite,
                     sf::Sprite& plateforme7Sprite, sf::Sprite& plateforme8Sprite,
                     sf::Sprite& plateforme9Sprite, sf::Sprite& plateforme10Sprite, sf::Sprite& obstacle1Sprite,
                     sf::Sprite& obstacle2Sprite, sf::Sprite& enemy1Sprite, sf::Sprite& enemy2Sprite,
                     sf::Sprite& enemy3Sprite,
                     sf::Sprite& finishSprite, float& limitTimeJump, bool& canPressLeft, bool& canPressRight,
                     float& parallaxOffset);
};
