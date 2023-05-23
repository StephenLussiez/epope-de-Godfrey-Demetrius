#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include <vector>


class GameEngine
{
public:
    GameEngine();
    int Gameloop();
    void GameInputs(sf::RenderWindow* window, Sprite* godfrey, sf::Time& deltaTime, float& limitTimeJump,
                    bool& canPressLeft, bool& canPressRight, float& parallaxOffset);
    void GameDrawing(sf::RenderWindow* window, Sprite* godfrey, std::vector<Sprite*> cartes, std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles, std::vector<Sprite*> ennemies, Sprite* finishSprite,
                     float& parallaxOffset);
    bool CheckCollision(Sprite* sprite1, Sprite* sprite2);
    void GamePhysics(sf::RenderWindow* window, Sprite* godfrey, sf::Time deltaTime,
                     std::vector<Sprite *> platformes, std::vector<Sprite*> obstacles, std::vector<Sprite*> ennemies,
                     Sprite* finish, float& limitTimeJump, bool& canPressLeft, bool& canPressRight,
                     float& parallaxOffset);

    bool IsPlayerAboveEnemy(Sprite* godfrey, Sprite* enemySprite);
    bool IsPlayerOnTheRight(Sprite* godfrey, Sprite* obstacle);
    bool IsPlayerOnTheLeft(Sprite* godfrey, Sprite* obstacle);
};
