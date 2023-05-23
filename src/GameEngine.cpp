#include "headers/GameEngine.h"
#include <iostream>
#include <SFML/Audio.hpp>// Inclure la bibliothèque SFML Audio
#include "headers/WindowManager.h"

GameEngine::GameEngine() {}


void GameEngine::GameInputs(sf::RenderWindow* window, Sprite* godfrey, sf::Time& deltaTime, float& limitTimeJump,
    bool& canPressLeft, bool& canPressRight, float& parallaxOffset)
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }

    // Contrôle du personnage
    float speed = 11.7f;
    float jumpHeight = -2.0f;
    static bool isJumping = false;
    static float jumpSpeed = 0.0f;
    static float jumpHeightRemaining = 0.0f;
    float deltaTimeSeconds = deltaTime.asSeconds();
    float jumpAcceleration = -12.81f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && canPressLeft)
    {
        parallaxOffset = speed;
        canPressRight = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && canPressRight)
    {
        parallaxOffset = -speed;
        canPressLeft = true;
    } else
    {
        parallaxOffset = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping && limitTimeJump <= 0.5f)
    {
        isJumping = true;
        jumpSpeed = 0.0f;
        jumpHeightRemaining = jumpHeight;
        limitTimeJump += deltaTimeSeconds;
    } else if (limitTimeJump > 1.0f && limitTimeJump < 2.0f)
    {
        limitTimeJump += deltaTimeSeconds;
        isJumping = false;
    } else if (limitTimeJump >= 2.0f)
    {
        limitTimeJump = 0.0f;
    }

    if (isJumping)
    {
        jumpSpeed += jumpAcceleration;
        godfrey->Move(0, jumpSpeed * 200 * deltaTimeSeconds);
        jumpHeightRemaining -= jumpSpeed;

        if (isJumping)
        {
            isJumping = false;
            jumpSpeed = 0.0f;
            jumpHeightRemaining = 0.0f;
        }
    }
}


void GameEngine::GameDrawing(sf::RenderWindow* window, Sprite* godfrey, std::vector<Sprite*> cartes, std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles, std::vector<Sprite*> ennemies, Sprite* finishSprite,
                                float& parallaxOffset)
{
    // Appliquer le décalage de parallaxe aux positions des cartes
    for (Sprite* it : cartes) {
        it->Move((parallaxOffset * 0.05f), 0);
    }
    for (Sprite* it : platformes) {
        it->Move((parallaxOffset * 0.1f), 0);
    }
    for (Sprite* it : obstacles) {
        it->Move((parallaxOffset * 0.1f), 0);
    }
    for (Sprite* it : ennemies) {
        it->Move((parallaxOffset * 0.1f), 0);
    }
    finishSprite->Move((parallaxOffset * 0.1f), 0);

    window->clear();
    for (Sprite* it : cartes) {
        it->Draw(window);
    }
    for (Sprite* it : platformes) {
        it->Draw(window);
    }
    for (Sprite* it : obstacles) {
        it->Draw(window);
    }
    for (Sprite* it : ennemies) {
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

bool GameEngine::CheckCollision(Sprite* sprite, std::vector<Sprite *> sprites)
{
    for (Sprite* it : sprites) {
        if (CheckCollision(sprite, it)) {
            return (true);
        }
    }
    return (false);
}

bool GameEngine::IsPlayerAboveEnemy(Sprite* godfrey, Sprite* enemySprite)
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
    std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles, std::vector<Sprite*> ennemies,
    Sprite* finish, float& limitTimeJump,
                             bool& canPressLeft, bool& canPressRight,
                             float& parallaxOffset)
{
    float speed = 0.0f;
    const float gravity = 3.81f;
    float deltaTimeSeconds = deltaTime.asSeconds();
    speed += gravity;

    // Vérification des collisions avec les autres sprites
    if (CheckCollision(godfrey, platformes)) {
        godfrey->Move(0, 0);
        limitTimeJump = 0.0f;
    } else {
        godfrey->Move(0, (speed + speed * deltaTimeSeconds));
    }

    for (Sprite* it : obstacles) {
        if (CheckCollision(godfrey, it)) {
                if (IsPlayerAboveEnemy(godfrey, it))
            {
                canPressLeft = true;
                canPressRight = true;
            } else if (IsPlayerOnTheRight(godfrey, it))
            {
                canPressLeft = false;
            } else if (IsPlayerOnTheLeft(godfrey, it))
            {
                canPressRight = false;
            }
            break;
        }
    }

    // Vérification de la collision avec les ennemis
    for (Sprite* it : ennemies) {
        if (CheckCollision(godfrey, it)) {
            if (IsPlayerAboveEnemy(godfrey, it))
            {
                std::cout << "il est mort";
                // Le joueur a sauté au-dessus de l'ennemi, supprimez enemy1Sprite
                it->set_position(-1000, -1000); // Déplacez l'ennemi en dehors de l'écran (penser a delete le sprite plus tard)
            }
            else
            {
                // Le joueur est entré en collision avec un ennemi, faites quelque chose (par exemple, affichez un message ou réinitialisez le niveau)
            }
            break;
        }
    }


    if (CheckCollision(godfrey, finish))
    {
        std::cout << "victory";
        godfrey->Move(0, 0);
    }
}

Sprite* init_godfrey()
{
    return (new Sprite("src/assets/Godfrey.png", 72, 152, sf::Vector2f{ 700, 300 }));
}   

std::vector<Sprite *> init_cartes()
{
    std::vector<Sprite *> sprites;
    Sprite* sprite;
    int carteSize = 1024;

    for (int nb = 0; nb < 10; nb += 1) {
        if (nb % 2 != 0) {
            sprite = new Sprite("src/assets/Carte1.png", 1024, 1024, sf::Vector2f{ -500.0f + (carteSize * nb), 0});
            sprites.push_back(sprite);
        }
        else {
            sprite = new Sprite("src/assets/Carte1bis.png", 1024, 1024, sf::Vector2f{ -500.0f+ (carteSize * nb), 0 });
            sprites.push_back(sprite);
        }
    }
    return (sprites);
}

std::vector<Sprite*> init_platformes()
{
    std::vector<Sprite*> sprites;
    Sprite* sprite;

    for (int nb = 0; nb < 10; nb += 1) {
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

    for (int nb = 0; nb < 2; nb += 1) {
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

    for (int nb = 0; nb < 2; nb += 1) {
        sprite = new Sprite("src/assets/monsterIdle.png", 1160, 119);
        sprites.push_back(sprite);
    }
    sprites[0]->set_position(platformes[2]->get_position().x + (platformes[2]->get_size().x),
        800);
    sprites[1]->set_position(platformes[6]->get_position().x + (platformes[6]->get_size().x),
        800);

    return (sprites);   
}

Sprite* init_finish(std::vector<Sprite*> platformes)
{
    return (new Sprite("src/assets/finish.png", 190, 565, 
        sf::Vector2f{ platformes[9]->get_position().x + (platformes[9]->get_size().x / 2), 335 }));
}

int GameEngine::Gameloop()
{
       sf::Clock clock;
    WindowManager* windowBox = new WindowManager();
    sf::RenderWindow* window = windowBox->CreateWindow(1920, 1080, "L'épopée de Goldfey Dimitrius");
    float limitTimeJump = 0.0f;
    bool canPressLeft = true;
    bool canPressRight = true;

    // Chargement de la texture pour le personnage
    Sprite* godfrey = init_godfrey();

    // Chargement des cartes en arrière plan
    std::vector<Sprite *> cartes = init_cartes();

    // Chargement des plateformes
    std::vector<Sprite*> platformes = init_platformes();

    // Chargement des obstacle
    std::vector<Sprite*> obstacles = init_obstacles(platformes);

    // Chargement des ennemi
    std::vector<Sprite*> ennemies = init_ennemies(platformes);

    // Chargement de la zone de fin
    Sprite* finishSprite = init_finish(platformes);

    float parallaxOffset = 0.0f;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("src/EpicMusic.ogg")) { }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(100.0f);
    sound.play();

    sf::Time deltaTime = clock.restart();

    while (window->isOpen())
    {
        GameInputs(window, godfrey, deltaTime, limitTimeJump, canPressLeft, canPressRight, parallaxOffset);
        GamePhysics(window, godfrey, deltaTime, platformes, obstacles, ennemies, finishSprite, limitTimeJump, canPressLeft, canPressRight,
            parallaxOffset);
        GameDrawing(window, godfrey, cartes, platformes, obstacles, ennemies, finishSprite, parallaxOffset);

        deltaTime = clock.restart();
    }

    return 0;
}
