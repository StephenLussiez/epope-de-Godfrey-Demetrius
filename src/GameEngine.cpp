#include "headers/GameEngine.h"
#include <iostream>
#include <memory>
#include <SFML/Audio.hpp>  // Inclure la bibliothèque SFML Audio
#include "headers/WindowManager.h"

GameEngine::GameEngine() {}


void GameEngine::GameInputs(sf::RenderWindow* window, Sprite* godfrey)
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }

    // Inputs de déplacements
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        m_godfreyAction = MoveLeft;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_godfreyAction = MoveRight;
    } 
    else {
        m_godfreyAction = None;
    }

    // Input de saut
    m_deltaTimeSeconds = m_deltaTime.asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_isJumping && m_limitTimeJump <= 0.5f)
    {
        m_isJumping = true;
        m_jumpSpeed = 0.0f;
        m_jumpHeightRemaining = m_jumpHeight;
        m_limitTimeJump += m_deltaTimeSeconds;
    }
    else if (m_limitTimeJump > 1.0f && m_limitTimeJump < 2.0f)
    {
        m_limitTimeJump += m_deltaTimeSeconds;
        m_isJumping = false;
    }
    else if (m_limitTimeJump >= 2.0f)
    {
        m_limitTimeJump = 0.0f;
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
}

void GameEngine::GamePhysics(sf::RenderWindow* window, Sprite* godfrey, std::vector<Sprite*> cartes,
    std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles,
    std::vector<Sprite*> ennemies,
    Sprite* finishSprite)
{
    float deltaTime = m_clock.getElapsedTime().asSeconds();
    std::cout << deltaTime << std::endl;

    // Mouvement du personnage/carte (parallax)
    if (m_godfreyAction == MoveLeft && m_canPressLeft)
    {
        m_parallaxOffset = m_speed;
        m_canPressRight = true;
    } else if (m_godfreyAction == MoveRight && m_canPressRight)
    {
        m_parallaxOffset = -m_speed;
        m_canPressLeft = true;
    } else
    {
        m_parallaxOffset = 0;
    }

    //Vérification des collisions avec les autres sprites
    Sprite* spr = GetSpriteCollision(godfrey, obstacles);

    if (CheckCollision(godfrey, platformes) || spr != nullptr)
    {
        godfrey->Move(0, 0);
        m_limitTimeJump = 0.0f;
        m_allowJump = true;
        m_limitTimeJump = 0.0f;
    }
    else
    {
        godfrey->Move(0, (m_speed + m_speed * deltaTime));
    }

    if (spr != nullptr)
    {
        if (IsPlayerAbove(godfrey, spr))
        {
            m_canPressLeft = true;
            m_canPressRight = true;
            m_allowJump = true;
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
            else {
                m_state = Defeat;
                // Le joueur est entré en collision avec un ennemi, faites quelque chose (par exemple, affichez un message ou réinitialisez le niveau)
            }
            break;
        }
    }

    //Condition de défaite
    if (godfrey->get_position().y > window->getSize().y)
    {
        m_state = Defeat;
    }
    // Vérification de la collision avec la ligne d'arrivée
    if (CheckCollision(godfrey, finishSprite))
    {
        m_state = Victory;
        godfrey->Move(0, 0);
    }

    // Update des déplacements
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

void GameEngine::GamePhysics(sf::RenderWindow* window, Sprite* godfrey, sf::Time deltaTime,
                             std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles,
                             std::vector<Sprite*> ennemies,
                             Sprite* finish, float& limitTimeJump,
                             bool& canPressLeft, bool& canPressRight, bool& victory, bool& defeat,
                             float& parallaxOffset)
{
    float speed = 0.0f;
    const float gravity = 3.81f;
    float deltaTimeSeconds = deltaTime.asSeconds();
    speed += gravity;
    Sprite* spr = GetSpriteCollision(godfrey, obstacles);
    // Vérification des collisions avec les autres sprites
    if (CheckCollision(godfrey, platformes) || spr != nullptr)
    {
        godfrey->Move(0, 0);
        limitTimeJump = 0.0f;
    } else
    {
        godfrey->Move(0, (speed + speed * deltaTimeSeconds));
    }


    if (spr != nullptr)
    {
        if (IsPlayerAbove(godfrey, spr))
        {
            canPressLeft = true;
            canPressRight = true;
        } else if (IsPlayerOnTheRight(godfrey, spr))
        {
            canPressLeft = false;
        } else if (IsPlayerOnTheLeft(godfrey, spr))
        {
            canPressRight = false;
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
            } else
            {
                defeat = true;
                // Le joueur est entré en collision avec un ennemi, faites quelque chose (par exemple, affichez un message ou réinitialisez le niveau)
            }
            break;
        }
    }

    if (CheckCollision(godfrey, finish))
    {
        victory = true;
        godfrey->Move(0, 0);
    }
}

Sprite* init_godfrey()
{
    return (new Sprite("src/assets/Godfrey.png", 72, 152, sf::Vector2f {700, 300}));
}

Sprite* init_godfreyWalk()
{
    return (new Sprite("src/assets/Godfrey-walk.png", 72, 152, sf::Vector2f {700, 300}));
}

std::vector<Sprite*> init_cartes()
{
    std::vector<Sprite*> sprites;
    Sprite* sprite;
    int carteSize = 1024;

    for (int nb = 0; nb < 10; nb += 1)
    {
        if (nb % 2 != 0)
        {
            sprite = new Sprite("src/assets/Carte1.png", 1024, 1024, sf::Vector2f {-500.0f + (carteSize * nb), 0});
            sprites.push_back(sprite);
        } else
        {
            sprite = new Sprite("src/assets/Carte1bis.png", 1024, 1024, sf::Vector2f {-500.0f + (carteSize * nb), 0});
            sprites.push_back(sprite);
        }
    }
    return (sprites);
}

std::vector<Sprite*> init_platformes()
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

std::vector<Sprite*> init_obstacles(std::vector<Sprite*> platformes)
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

std::vector<Sprite*> init_ennemies(std::vector<Sprite*> platformes)
{
    std::vector<Sprite*> sprites;
    Sprite* sprite;

    for (int nb = 0; nb < 2; nb += 1)
    {
        sprite = new Sprite("src/assets/monsterIdle.png", 1160, 119);
        sprites.push_back(sprite);
    }
    sprites[0]->set_position(platformes[2]->get_position().x + (platformes[2]->get_size().x) + 200,
                             800);
    sprites[1]->set_position(platformes[6]->get_position().x + (platformes[6]->get_size().x),
                             800);

    return (sprites);
}

Sprite* init_finish(std::vector<Sprite*> platformes)
{
    return (new Sprite("src/assets/finish.png", 190, 565,
                       sf::Vector2f {platformes[9]->get_position().x + (platformes[9]->get_size().x / 2), 335}));
}

Sprite* init_victory()
{
    Sprite* sprite;
    return (new Sprite("src/assets/victory.png", 790, 1065,
                       sf::Vector2f {750, 450}));
}

Sprite* init_defeat()
{
    Sprite* sprite;
    return (new Sprite("src/assets/defeat.png", 790, 1065,
                       sf::Vector2f {750, 450}));
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

    
    m_deltaTime = m_clock.restart();
    while (window->isOpen())
    {
        GameInputs(window, godfrey);
        GamePhysics(window, godfrey,cartes, platformes, obstacles, ennemies, finishSprite);
        GameDrawing(window, godfrey, cartes, platformes, obstacles, ennemies, finishSprite, victoryScreen, defeatScreen);
        m_deltaTime = m_clock.restart();
    }

    return 0;
}
