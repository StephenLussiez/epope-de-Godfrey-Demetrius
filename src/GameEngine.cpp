#include "headers/GameEngine.h"
#include <iostream>
#include <memory>
#include <SFML/Audio.hpp>  // Inclure la bibliothèque SFML Audio
#include "headers/WindowManager.h"

GameEngine::GameEngine() {
    
}


void GameEngine::GameInputs(sf::RenderWindow* window)
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }

    switch (event.KeyPressed) {
    case sf::Keyboard::Q:
        GodfreyAction = MoveLeft;
        break;
    case sf::Keyboard::D:
        GodfreyAction = MoveRight;
        break;
    case sf::Keyboard::Space:
        GodfreyAction = Jump;
        break;
    }
}

void GameEngine::GamePhysics(sf::RenderWindow* window, Sprite* godfrey, std::vector<Sprite*> cartes,
    std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles,
    std::vector<Sprite*> ennemies,
    Sprite* finishSprite)
{
    if (GodfreyAction == MoveLeft && m_canPressLeft)
    {
        m_parallaxOffset = m_speed;
        m_canPressRight = true;
    } else if (GodfreyAction == MoveRight && m_canPressRight)
    {
        m_parallaxOffset = -m_speed;
        m_canPressLeft = true;
    } else
    {
        m_parallaxOffset = 0;
    }

    if (GodfreyAction == Jump && !m_isJumping && m_limitTimeJump <= 0.5f)
    {
        m_isJumping = true;
        m_jumpSpeed = 0.0f;
        m_jumpHeightRemaining = m_jumpHeight;
        m_limitTimeJump += m_deltaTimeSeconds;
    } else if (m_limitTimeJump > 1.0f && m_limitTimeJump < 2.0f)
    {
        m_limitTimeJump += m_deltaTimeSeconds;
        m_isJumping = false;
    } else if (m_limitTimeJump >= 2.0f)
    {
        m_limitTimeJump = 0.0f;
    }

    if (godfrey->get_position().y > window->getSize().y)
    {
        m_state = Defeat;
    }

    if (m_isJumping)
    {
        m_jumpSpeed += m_jumpAcceleration;
        godfrey->Move(0, m_jumpSpeed * 200 * m_deltaTimeSeconds);
        m_jumpHeightRemaining -= m_jumpSpeed;

        if (m_isJumping)
        {
            m_isJumping = false;
            m_jumpSpeed = 0.0f;
            m_jumpHeightRemaining = 0.0f;
        }
    }

    Sprite* spr = GetSpriteCollision(godfrey, obstacles);

    // Vérification des collisions avec les autres sprites
    if (CheckCollision(godfrey, platformes) || spr != nullptr)
    {
        godfrey->Move(0, 0);
        m_limitTimeJump = 0.0f;
    }
    else
    {
        godfrey->Move(0, (m_speed + m_speed * m_deltaTimeSeconds));
    }


    if (spr != nullptr)
    {
        if (IsPlayerAbove(godfrey, spr))
        {
            m_canPressLeft = true;
            m_canPressRight = true;
        }
        else if (IsPlayerOnTheRight(godfrey, spr))
        {
            m_canPressLeft = false;
        }
        else if (IsPlayerOnTheLeft(godfrey, spr))
        {
            m_canPressRight = false;
        }
    }

    // Vérification de la collision avec les ennemis
    for (Sprite* it : ennemies)
    {
        if (CheckCollision(godfrey, it))
        {
            if (IsPlayerAbove(godfrey, it))
            {
                std::cout << "il est mort";
                // Le joueur a sauté au-dessus de l'ennemi, supprimez enemy1Sprite
                it->set_position(-1000, -1000);
                // Déplacez l'ennemi en dehors de l'écran (penser a delete le sprite plus tard)
            }
            else
            {
                m_state = Defeat;
                // Le joueur est entré en collision avec un ennemi, faites quelque chose (par exemple, affichez un message ou réinitialisez le niveau)
            }
            break;
        }
    }

    if (CheckCollision(godfrey, finishSprite))
    {
        m_state = Victory;
        godfrey->Move(0, 0);
    }

    for (Sprite* it : cartes)
    {
        it->Move((m_parallaxOffset * 0.05f), 0);
    }
    for (Sprite* it : platformes)
    {
        it->Move((m_parallaxOffset * 0.1f), 0);
    }
    for (Sprite* it : obstacles)
    {
        it->Move((m_parallaxOffset * 0.1f), 0);
    }
    for (Sprite* it : ennemies)
    {
        it->Move((m_parallaxOffset * 0.1f), 0);
    }
    finishSprite->Move((m_parallaxOffset * 0.1f), 0);
}

void gameUpdate();

void GameEngine::GameDrawing(sf::RenderWindow* window, Sprite* godfrey, std::vector<Sprite*> cartes,
                             std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles,
                             std::vector<Sprite*> ennemies, Sprite* finishSprite, Sprite* victoryScreen, Sprite* defeatScreen)
{
    window->clear();

    switch (m_state)
    {
    case GameEngine::Playing:
        break;
    case GameEngine::Victory:
        victoryScreen->Draw(window);
        break;
    case GameEngine::Defeat:
        defeatScreen->Draw(window);
        break;
    }
    
    // Appliquer le décalage de parallaxe aux positions des cartes
    for (Sprite* it : cartes)
    {
        it->Draw(window);
    }
    for (Sprite* it : platformes)
    {
        it->Draw(window);
    }
    for (Sprite* it : obstacles)
    {
        it->Draw(window);
    }
    for (Sprite* it : ennemies)
    {
        it->Draw(window);
    }
    finishSprite->Draw(window);
    godfrey->Draw(window);
    window->display();
}

bool GameEngine::CheckCollision(Sprite* sprite1, Sprite* sprite2)
{
    return sprite1->intersects(sprite2);
}

bool GameEngine::CheckCollision(Sprite* sprite, std::vector<Sprite*> sprites)
{
    for (Sprite* it : sprites)
    {
        if (CheckCollision(sprite, it))
        {
            return (true);
        }
    }
    return (false);
}

Sprite* GameEngine::GetSpriteCollision(Sprite* sprite, std::vector<Sprite*> sprites)
{
    for (Sprite* it : sprites)
    {
        if (CheckCollision(sprite, it))
        {
            return (it);
        }
    }
    return (nullptr);
}

bool GameEngine::IsPlayerAbove(Sprite* godfrey, Sprite* enemySprite)
{
    sf::FloatRect playerBounds = godfrey->get_globalBounds();
    sf::FloatRect enemyBounds = enemySprite->get_globalBounds();

    // Vérifie si le bas du joueur est au-dessus du haut de l'ennemi
    return playerBounds.top + playerBounds.height < enemyBounds.top + 5;
}

bool GameEngine::IsPlayerOnTheRight(Sprite* godfrey, Sprite* obstacle)
{
    sf::FloatRect playerBounds = godfrey->get_globalBounds();
    sf::FloatRect obstacleBounds = obstacle->get_globalBounds();

    // Vérifie si le bas du joueur est au-dessus du haut de l'ennemi
    return godfrey->get_position().x + playerBounds.width > obstacle->get_position().x + obstacleBounds.width + 5;
}

bool GameEngine::IsPlayerOnTheLeft(Sprite* godfrey, Sprite* obstacle)
{
    sf::FloatRect playerBounds = godfrey->get_globalBounds();
    sf::FloatRect obstacleBounds = obstacle->get_globalBounds();

    // Vérifie si le bas du joueur est au-dessus du haut de l'ennemi
    return godfrey->get_position().x + playerBounds.width < obstacle->get_position().x + 10;
}

int GameEngine::Gameloop()
{
    WindowManager* windowBox = new WindowManager();
    sf::RenderWindow* window = windowBox->CreateWindow(1920, 1080, "L'épopée de Godfey Dimitrius");

    InitParameters();

    // Chargement de la texture pour le personnage
    Sprite* godfrey = init_godfrey();

    // Chargement des cartes en arrière plan
    std::vector<Sprite*> cartes = init_cartes();

    // Chargement des plateformes
    std::vector<Sprite*> platformes = init_platformes();

    // Chargement des obstacle
    std::vector<Sprite*> obstacles = init_obstacles(platformes);

    // Chargement des ennemi
    std::vector<Sprite*> ennemies = init_ennemies(platformes);

    // Chargement de la zone de fin
    Sprite* finishSprite = init_finish(platformes);

    // Chargement de l'écran de victoire 
    Sprite* victoryScreen = init_victory();

    // Chargement de l'écran de défaite 
    Sprite* defeatScreen = init_defeat();

    

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("src/EpicMusic.ogg")) { }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(100.0f);
    sound.play();

    

    while (window->isOpen())
    {
        GameInputs(window);
        GamePhysics(window, godfrey, platformes, cartes, obstacles, ennemies, finishSprite);
        GameDrawing(window, godfrey, cartes, platformes, obstacles, ennemies, finishSprite, victoryScreen, defeatScreen);
        m_clock.restart();
    }

    return 0;
}
