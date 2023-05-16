#include "headers/GameEngine.h"
#include <iostream>
#include "headers/WindowManager.h"

GameEngine::GameEngine() {}

void GameEngine::GameInputs(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Time deltaTime, sf::Sprite& plateformSprite1)
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
    float speed = 15.0f;
    float jumpHeight = -2.0f;
    static bool isJumping = false;
    static float jumpSpeed = 0.0f;
    static float jumpHeightRemaining = 0.0f;
    float deltaTimeSeconds = deltaTime.asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        playerSprite.move(-speed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerSprite.move(speed, 0);
    }
    
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping)
    {
        isJumping = true;
        jumpSpeed = 0.0f;
        jumpHeightRemaining = jumpHeight;
    }

    if (isJumping)
    {
        float jumpAcceleration = -18.81f;
        jumpSpeed += jumpAcceleration;
        playerSprite.move(0, jumpSpeed);
        jumpHeightRemaining -= jumpSpeed;

        if (jumpHeightRemaining >= -2.0f)
        {
            isJumping = false;
            jumpSpeed = 0.0f;
            jumpHeightRemaining = 0.0f;
        }
    }
    
}

void GameEngine::GameDrawing(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Sprite& carte1Sprite, sf::Sprite& carte2Sprite, sf::Sprite& plateforme1Sprite)
{
    window->clear();
    window->draw(carte1Sprite);
    window->draw(carte2Sprite);
    window->draw(playerSprite);
    window->draw(plateforme1Sprite);
    window->display();
}

bool GameEngine::CheckCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    return bounds1.intersects(bounds2);
}

void GameEngine::GamePhysics(sf::Sprite& playerSprite, sf::Time deltaTime, sf::Sprite& plateformSprite1)
{
    float speed = 0.0f;
    const float gravity = 1.81f;
    float deltaTimeSeconds = deltaTime.asSeconds();
    /*if (playerSprite.getPosition().y >= 800)
    {
        
    }*/
    

    // Vérification des collisions avec les autres sprites
    if (CheckCollision(playerSprite, plateformSprite1) /*|| CheckCollision(playerSprite, carte2Sprite)*/)
    {
        playerSprite.move(0, 0);
        //enemySprite.move(0, speed);
    }
    else
    {
        speed += gravity;
        playerSprite.move(0, speed);
    }
}



int GameEngine::Gameloop()
{
    sf::Clock clock;
    WindowManager* windowBox = new WindowManager();
    sf::RenderWindow* window = windowBox->CreateWindow(1920, 1080, "L'épopée de Goldfey Dimitrius");
    
    // Chargement de la texture pour le personnage
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("src/assets/Godfrey.png")) {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }
    sf::Sprite playerSprite(playerTexture);
    sf::Vector2f playerPosition(0, 300);
    playerSprite.setPosition(playerPosition);

    // Chargement de la première carte
    sf::Texture carte1Texture;
    if (!carte1Texture.loadFromFile("src/assets/Carte1.png")) {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }
    
    sf::Sprite carte1Sprite(carte1Texture);
    sf::Vector2f carte1Position(0, 0);
    carte1Sprite.setPosition(carte1Position);

    // Chargement de la deuxième carte
    sf::Texture carte2Texture;
    
    if (!carte2Texture.loadFromFile("src/assets/Carte3.png")) {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }
    
    sf::Sprite carte2Sprite(carte2Texture);
    sf::Vector2f carte2Position(carte1Texture.getSize().x, 0);
    carte2Sprite.setPosition(carte2Position);

    // Chargement de la première carte
    sf::Texture plateforme1Texture;
    if (!plateforme1Texture.loadFromFile("src/assets/plateforme1.png")) {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite plateforme1Sprite(carte1Texture);
    sf::Vector2f plateforme1Position(0, 900);
    plateforme1Sprite.setPosition(plateforme1Position);
    
    sf::Time deltaTime = clock.restart();
    
    while (window->isOpen()) {
        GameInputs(window, playerSprite, deltaTime, plateforme1Sprite);
        GameDrawing(window, playerSprite,carte1Sprite, carte2Sprite, plateforme1Sprite);
        GamePhysics(playerSprite, deltaTime, plateforme1Sprite);
        
        /*std::cout << playerSprite.getPosition().x;
        std::cout << playerSprite.getPosition().y;*/
        
    }
    
    
    return 0;
}

