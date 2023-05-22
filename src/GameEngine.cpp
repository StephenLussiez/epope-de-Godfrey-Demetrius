#include "headers/GameEngine.h"
#include <iostream>
#include "headers/WindowManager.h"
#include "SFML/Audio.hpp"  // Inclure la bibliothèque SFML Audio

GameEngine::GameEngine() {}

void GameEngine::GameInputs(sf::RenderWindow* window, Sprite* playerSprite, sf::Time& deltaTime,
                            float& parallaxOffset)
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        parallaxOffset = speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        parallaxOffset = -speed;
    } else
    {
        parallaxOffset = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping)
    {
        isJumping = true;
        jumpSpeed = 0.0f;
        jumpHeightRemaining = jumpHeight;
    }

    if (isJumping)
    {
        float jumpAcceleration = -12.81f;
        jumpSpeed += jumpAcceleration;
        playerSprite->Move(0, jumpSpeed * 200 * deltaTimeSeconds);
        jumpHeightRemaining -= jumpSpeed;

        if (jumpHeightRemaining >= -2.0f)
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

void GameEngine::GamePhysics(sf::RenderWindow* window, Sprite* godfrey, sf::Time deltaTime,
    std::vector<Sprite*> platformes, std::vector<Sprite*> obstacles, std::vector<Sprite*> ennemies,
    Sprite* finish)
{
    float speed = 0.0f;
    const float gravity = 3.81f;
    float deltaTimeSeconds = deltaTime.asSeconds();
    speed += gravity;
    godfrey->Move(0, (speed + speed * deltaTimeSeconds));

    // Vérification des collisions avec les autres sprites
    for (Sprite* it : platformes) {
        if (CheckCollision(godfrey, it)) {
            godfrey->Move(0, 0);
            break;
        }
    }

    for (Sprite* it : obstacles) {
        if (CheckCollision(godfrey, it)) {
            godfrey->Move(0, 0);
            break;
        }
    }

    for (Sprite* it : ennemies) {
        if (CheckCollision(godfrey, it)) {
            std::cout << "t'es mort ! t'es mort ! t'es mort !";
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

std::vector<Sprite *> init_ennemies(std::vector<Sprite*> platformes)
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

    // Chargement de la musique
    sf::Music music;
    if (!music.openFromFile("src/assets/EpicMusic.ogg")) { }

    // Réglages de la musique
    music.setVolume(50); // Définir le volume (0-100)
    music.setLoop(true); // Définir la musique en mode boucle

    // Lancer la musique
    music.play();

    sf::Time deltaTime = clock.restart();

    while (window->isOpen())
    {
        GameInputs(window, godfrey, deltaTime, parallaxOffset);
        GamePhysics(window, godfrey, deltaTime, platformes, obstacles, ennemies, finishSprite);
        GameDrawing(window, godfrey, cartes, platformes, obstacles, ennemies, finishSprite, parallaxOffset);
        deltaTime = clock.restart();
    }

    return 0;
}
