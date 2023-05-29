#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Sprite.h"


class GameEngine
{

private:
    enum PlayerAction {
        MoveRight,
        MoveLeft,
        Jump
    };

    enum GameState {
        Playing,
        Victory,
        Defeat
    };

    PlayerAction GodfreyAction;
    GameState m_state;

    float m_speed;
    float m_jumpHeight;
    bool m_isJumping;
    float m_jumpSpeed;
    float m_jumpHeightRemaining;
    float m_jumpAcceleration;
    float m_deltaTimeSeconds;
    float m_gravity;
    float m_limitTimeJump;
    bool m_canPressLeft;
    bool m_canPressRight;
    sf::Clock m_clock;
    float m_parallaxOffset;

public:
    GameEngine();
    void InitParameters();
    Sprite* init_godfrey();
    std::vector<Sprite*> init_cartes();
    std::vector<Sprite*> init_platformes();
    std::vector<Sprite*> init_obstacles(std::vector<Sprite*> platformes);
    std::vector<Sprite*> init_ennemies(std::vector<Sprite*> platformes);
    Sprite* init_finish(std::vector<Sprite*> platformes);
    Sprite* init_victory();
    Sprite* init_defeat();

    int Gameloop();
    void GameInputs(sf::RenderWindow* window);
    void GamePhysics(sf::RenderWindow* window, Sprite* godfrey, std::vector<Sprite*> cartes,
                     std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles, std::vector<Sprite*> ennemies,
                     Sprite* finish);
    void gameUpdate();
    void GameDrawing(sf::RenderWindow* window, Sprite* godfrey, std::vector<Sprite*> cartes,
                     std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles, std::vector<Sprite*> ennemies,
                     Sprite* finishSprite, Sprite* victoryScreen, Sprite* defeatScreen);
    bool CheckCollision(Sprite* sprite1, Sprite* sprite2);
    bool CheckCollision(Sprite* sprite, std::vector<Sprite*> sprites);
    Sprite* GetSpriteCollision(Sprite* sprite, std::vector<Sprite*> sprites);
    bool IsPlayerAbove(Sprite* godfrey, Sprite* enemySprite);
    bool IsPlayerOnTheRight(Sprite* godfrey, Sprite* obstacle);
    bool IsPlayerOnTheLeft(Sprite* godfrey, Sprite* obstacle);
};
