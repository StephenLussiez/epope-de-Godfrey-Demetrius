#pragma once
#include "headers/GameEngine.h"
#include "SFML/System/Clock.hpp"

void GameEngine::InitParameters()
{
    m_speed = 11.7f;
    m_jumpHeight = -2.0f;
    m_allowJump = false;
    m_isJumping = false;
    m_jumpSpeed = 0.0f;
    m_jumpHeightRemaining = 0.0f;
    m_jumpAcceleration = -12.81f;
    m_gravity = 3.81f;
    m_limitTimeJump = 0.0f;
    m_canPressLeft = true;
    m_canPressRight = true;
    m_parallaxOffset = 0.0f;
    m_godfreyAction = None;
    m_state = Playing;
    m_clock.restart();
}

Sprite* GameEngine::init_godfrey()
{
    return (new Sprite("src/assets/Godfrey.png", 72, 152, sf::Vector2f{ 700, 300 }));
}

std::vector<Sprite*> GameEngine::init_cartes()
{
    std::vector<Sprite*> sprites;
    Sprite* sprite;
    int carteSize = 1024;

    for (int nb = 0; nb < 10; nb += 1)
    {
        if (nb % 2 != 0)
        {
            sprite = new Sprite("src/assets/Carte1.png", 1024, 1024, sf::Vector2f{ -500.0f + (carteSize * nb), 0 });
            sprites.push_back(sprite);
        }
        else
        {
            sprite = new Sprite("src/assets/Carte1bis.png", 1024, 1024, sf::Vector2f{ -500.0f + (carteSize * nb), 0 });
            sprites.push_back(sprite);
        }
    }
    return (sprites);
}

std::vector<Sprite*> GameEngine::init_platformes()
{
    std::vector<Sprite*> sprites;
    Sprite* sprite;

    for (int nb = 0; nb < 10; nb += 1)
    {
        sprite = new Sprite("src/assets/platforme1.png", 1160, 119);
        sprites.push_back(sprite);
    }
    sprites[0]->set_position(0, 900);
    sprites[1]->set_position(sprites[0]->get_size().x + 200, 900);
    sprites[2]->set_position(sprites[1]->get_position().x + sprites[1]->get_size().x, 900);
    sprites[3]->set_position(sprites[2]->get_position().x + sprites[2]->get_size().x + 200, 900);
    sprites[4]->set_position(sprites[3]->get_position().x + sprites[3]->get_size().x, 900);
    sprites[5]->set_position(sprites[4]->get_position().x + sprites[4]->get_size().x, 900);
    sprites[6]->set_position(sprites[5]->get_position().x + sprites[5]->get_size().x + 200, 900);
    sprites[7]->set_position(sprites[6]->get_position().x + sprites[6]->get_size().x, 900);
    sprites[8]->set_position(sprites[7]->get_position().x + sprites[7]->get_size().x + 250, 900);
    sprites[9]->set_position(sprites[8]->get_position().x + sprites[8]->get_size().x, 900);

    return (sprites);
}

std::vector<Sprite*> GameEngine::init_obstacles(std::vector<Sprite*> platformes)
{
    std::vector<Sprite*> sprites;
    Sprite* sprite;

    for (int nb = 0; nb < 2; nb += 1)
    {
        sprite = new Sprite("src/assets/obstacle1.png", 1160, 119);
        sprites.push_back(sprite);
    }
    sprites[0]->set_position(platformes[5]->get_position().x + (platformes[5]->get_size().x / 3),
        645);
    sprites[1]->set_position(platformes[6]->get_position().x + (platformes[6]->get_size().x / 3),
        645);

    return (sprites);
}

std::vector<Sprite*> GameEngine::init_ennemies(std::vector<Sprite*> platformes)
{
    std::vector<Sprite*> sprites;
    Sprite* sprite;

    for (int nb = 0; nb < 2; nb += 1)
    {
        sprite = new Sprite("src/assets/monsterIdle.png", 1160, 119);
        sprites.push_back(sprite);
    }
    sprites[0]->set_position(platformes[2]->get_position().x + (platformes[2]->get_size().x),
        800);
    sprites[1]->set_position(platformes[6]->get_position().x + (platformes[6]->get_size().x),
        800);

    return (sprites);
}

Sprite* GameEngine::init_finish(std::vector<Sprite*> platformes)
{
    return (new Sprite("src/assets/finish.png", 190, 565,
        sf::Vector2f{ platformes[9]->get_position().x + (platformes[9]->get_size().x / 2), 335 }));
}

Sprite* GameEngine::init_victory()
{
    Sprite* sprite;
    return (new Sprite("src/assets/victory.png", 790, 1065,
        sf::Vector2f{ 750, 450 }));
}

Sprite* GameEngine::init_defeat()
{
    Sprite* sprite;
    return (new Sprite("src/assets/defeat.png", 790, 1065,
        sf::Vector2f{ 750, 450 }));
}