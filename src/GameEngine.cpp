#include "headers/GameEngine.h"
#include <iostream>
#include "headers/WindowManager.h"

GameEngine::GameEngine() {}

void GameEngine::GameInputs(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Time& deltaTime,
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
    float speed = 8.0f;
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
        playerSprite.move(0, jumpSpeed * 200 * deltaTimeSeconds);
        jumpHeightRemaining -= jumpSpeed;

        if (jumpHeightRemaining >= -2.0f)
        {
            isJumping = false;
            jumpSpeed = 0.0f;
            jumpHeightRemaining = 0.0f;
        }
    }
}

void GameEngine::GameDrawing(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Sprite& carte1Sprite,
                             sf::Sprite& carte2Sprite, sf::Sprite& carte3Sprite,
                             sf::Sprite& carte4Sprite, sf::Sprite& carte5Sprite,
                             sf::Sprite& carte6Sprite, sf::Sprite& carte7Sprite,
                             sf::Sprite& carte8Sprite, sf::Sprite& carte9Sprite,
                             sf::Sprite& carte10Sprite, sf::Sprite& plateforme1Sprite, sf::Sprite& plateforme2Sprite,
                             sf::Sprite& plateforme3Sprite, sf::Sprite& plateforme4Sprite,
                             sf::Sprite& plateforme5Sprite, sf::Sprite& plateforme6Sprite,
                             sf::Sprite& plateforme7Sprite, sf::Sprite& plateforme8Sprite,
                             sf::Sprite& plateforme9Sprite, sf::Sprite& plateforme10Sprite, sf::Sprite& finishSprite,
                             float& parallaxOffset)
{
    // Appliquer le décalage de parallaxe aux positions des cartes
    carte1Sprite.move((parallaxOffset * 0.05f), 0);
    carte2Sprite.move((parallaxOffset * 0.05f), 0);
    carte3Sprite.move((parallaxOffset * 0.05f), 0);
    carte4Sprite.move((parallaxOffset * 0.05f), 0);
    carte5Sprite.move((parallaxOffset * 0.05f), 0);
    carte6Sprite.move((parallaxOffset * 0.05f), 0);
    carte7Sprite.move((parallaxOffset * 0.05f), 0);
    carte8Sprite.move((parallaxOffset * 0.05f), 0);
    carte9Sprite.move((parallaxOffset * 0.05f), 0);
    carte10Sprite.move((parallaxOffset * 0.05f), 0);
    plateforme1Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme2Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme3Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme4Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme5Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme6Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme7Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme8Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme9Sprite.move((parallaxOffset * 0.1f), 0);
    plateforme10Sprite.move((parallaxOffset * 0.1f), 0);
    finishSprite.move((parallaxOffset * 0.1f), 0);

    window->clear();
    window->draw(carte1Sprite);
    window->draw(carte2Sprite);
    window->draw(carte3Sprite);
    window->draw(carte4Sprite);
    window->draw(carte5Sprite);
    window->draw(carte6Sprite);
    window->draw(carte7Sprite);
    window->draw(carte8Sprite);
    window->draw(carte9Sprite);
    window->draw(carte10Sprite);
    window->draw(playerSprite);
    window->draw(plateforme1Sprite);
    window->draw(plateforme2Sprite);
    window->draw(plateforme3Sprite);
    window->draw(plateforme4Sprite);
    window->draw(plateforme5Sprite);
    window->draw(plateforme6Sprite);
    window->draw(plateforme7Sprite);
    window->draw(plateforme8Sprite);
    window->draw(plateforme9Sprite);
    window->draw(plateforme10Sprite);
    window->draw(finishSprite);
    window->display();
}


bool GameEngine::CheckCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    return bounds1.intersects(bounds2);
}

void GameEngine::GamePhysics(sf::Sprite& playerSprite, sf::Time deltaTime, sf::Sprite& plateformSprite1,
                             sf::Sprite& plateforme2Sprite,
                             sf::Sprite& plateforme3Sprite, sf::Sprite& plateforme4Sprite,
                             sf::Sprite& plateforme5Sprite, sf::Sprite& plateforme6Sprite,
                             sf::Sprite& plateforme7Sprite, sf::Sprite& plateforme8Sprite,
                             sf::Sprite& plateforme9Sprite, sf::Sprite& plateforme10Sprite, sf::Sprite& finishSprite)
{
    float speed = 0.0f;
    const float gravity = 3.81f;
    float deltaTimeSeconds = deltaTime.asSeconds();

    speed += gravity;

    // Vérification des collisions avec les autres sprites
    if (CheckCollision(playerSprite, plateformSprite1) || CheckCollision(playerSprite, plateforme2Sprite) ||
        CheckCollision(playerSprite, plateforme3Sprite) || CheckCollision(playerSprite, plateforme4Sprite) ||
        CheckCollision(playerSprite, plateforme5Sprite) || CheckCollision(playerSprite, plateforme6Sprite) ||
        CheckCollision(playerSprite, plateforme7Sprite) || CheckCollision(playerSprite, plateforme8Sprite) ||
        CheckCollision(playerSprite, plateforme9Sprite) || CheckCollision(playerSprite, plateforme10Sprite))
    {
        playerSprite.move(0, 0);
        //enemySprite.move(0, speed);
    } else
    {
        playerSprite.move(0, (speed + speed * deltaTimeSeconds));
        // Mettre à jour le décalage de parallaxe en fonction de la vitesse du personnage
    }

    if (CheckCollision(playerSprite, finishSprite))
    {
        std::cout << "victory";
        playerSprite.move(0, 0);
    }
}


int GameEngine::Gameloop()
{
    sf::Clock clock;
    WindowManager* windowBox = new WindowManager();
    sf::RenderWindow* window = windowBox->CreateWindow(1920, 1080, "L'épopée de Goldfey Dimitrius");

    // Chargement de la texture pour le personnage
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("src/assets/Godfrey.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }
    sf::Sprite playerSprite(playerTexture);
    sf::Vector2f playerPosition(700, 300);
    playerSprite.setPosition(playerPosition);

    // Chargement de la première carte
    sf::Texture carte1Texture;
    if (!carte1Texture.loadFromFile("src/assets/Carte1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte1Sprite(carte1Texture);
    sf::Vector2f carte1Position(-500, 0);
    carte1Sprite.setPosition(carte1Position);

    // Chargement de la deuxième carte
    sf::Texture carte2Texture;

    if (!carte2Texture.loadFromFile("src/assets/Carte1bis.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte2Sprite(carte2Texture);
    sf::Vector2f carte2Position(carte1Sprite.getPosition().x + carte1Sprite.getGlobalBounds().width, 0);
    carte2Sprite.setPosition(carte2Position);

    // Chargement de la troisieme carte
    sf::Texture carte3Texture;
    if (!carte3Texture.loadFromFile("src/assets/Carte1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte3Sprite(carte3Texture);
    sf::Vector2f carte3Position(carte2Sprite.getPosition().x + carte2Sprite.getGlobalBounds().width, 0);
    carte3Sprite.setPosition(carte3Position);

    // Chargement de la quatrieme carte
    sf::Texture carte4Texture;

    if (!carte4Texture.loadFromFile("src/assets/Carte1bis.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte4Sprite(carte4Texture);
    sf::Vector2f carte4Position(carte3Sprite.getPosition().x + carte3Sprite.getGlobalBounds().width, 0);
    carte4Sprite.setPosition(carte4Position);

    // Chargement de la cinquième carte
    sf::Texture carte5Texture;
    if (!carte5Texture.loadFromFile("src/assets/Carte1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte5Sprite(carte5Texture);
    sf::Vector2f carte5Position(carte4Sprite.getPosition().x + carte4Sprite.getGlobalBounds().width, 0);
    carte5Sprite.setPosition(carte5Position);

    // Chargement de la sixieme carte
    sf::Texture carte6Texture;

    if (!carte6Texture.loadFromFile("src/assets/Carte1bis.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte6Sprite(carte6Texture);
    sf::Vector2f carte6Position(carte5Sprite.getPosition().x + carte5Sprite.getGlobalBounds().width, 0);
    carte6Sprite.setPosition(carte6Position);

    // Chargement de la septieme carte
    sf::Texture carte7Texture;
    if (!carte7Texture.loadFromFile("src/assets/Carte1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte7Sprite(carte7Texture);
    sf::Vector2f carte7Position(carte6Sprite.getPosition().x + carte6Sprite.getGlobalBounds().width, 0);
    carte7Sprite.setPosition(carte7Position);

    // Chargement de la huitieme carte
    sf::Texture carte8Texture;

    if (!carte8Texture.loadFromFile("src/assets/Carte1bis.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte8Sprite(carte8Texture);
    sf::Vector2f carte8Position(carte7Sprite.getPosition().x + carte7Sprite.getGlobalBounds().width, 0);
    carte8Sprite.setPosition(carte8Position);

    // Chargement de la septieme carte
    sf::Texture carte9Texture;
    if (!carte9Texture.loadFromFile("src/assets/Carte1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte9Sprite(carte9Texture);
    sf::Vector2f carte9Position(carte8Sprite.getPosition().x + carte8Sprite.getGlobalBounds().width, 0);
    carte9Sprite.setPosition(carte9Position);

    // Chargement de la huitieme carte
    sf::Texture carte10Texture;

    if (!carte10Texture.loadFromFile("src/assets/Carte1bis.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite carte10Sprite(carte10Texture);
    sf::Vector2f carte10Position(carte9Sprite.getPosition().x + carte9Sprite.getGlobalBounds().width, 0);
    carte10Sprite.setPosition(carte10Position);

    // Chargement de la première plateforme
    sf::Texture plateforme1Texture;
    if (!plateforme1Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme1Sprite(plateforme1Texture);
    sf::Vector2f plateforme1Position(0, 900);
    plateforme1Sprite.setPosition(plateforme1Position);

    // Chargement de la première plateforme
    sf::Texture plateforme2Texture;
    if (!plateforme1Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme2Sprite(plateforme1Texture);
    sf::Vector2f plateforme2Position(plateforme1Sprite.getGlobalBounds().width, 900);
    plateforme2Sprite.setPosition(plateforme2Position);

    // Chargement de la première plateforme
    sf::Texture plateforme3Texture;
    if (!plateforme1Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme3Sprite(plateforme1Texture);
    sf::Vector2f plateforme3Position(plateforme2Sprite.getPosition().x + plateforme2Sprite.getGlobalBounds().width,
                                     900);
    plateforme3Sprite.setPosition(plateforme3Position);

    // Chargement de la première plateforme
    sf::Texture plateforme4Texture;
    if (!plateforme1Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme4Sprite(plateforme1Texture);
    sf::Vector2f plateforme4Position(plateforme3Sprite.getPosition().x + plateforme3Sprite.getGlobalBounds().width,
                                     900);
    plateforme4Sprite.setPosition(plateforme4Position);

    // Chargement de la première plateforme
    sf::Texture plateforme5Texture;
    if (!plateforme1Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme5Sprite(plateforme1Texture);
    sf::Vector2f plateforme5Position(plateforme4Sprite.getPosition().x + plateforme4Sprite.getGlobalBounds().width,
                                     900);
    plateforme5Sprite.setPosition(plateforme5Position);

    // Chargement de la première plateforme
    sf::Texture plateforme6Texture;
    if (!plateforme5Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme6Sprite(plateforme1Texture);
    sf::Vector2f plateforme6Position(plateforme5Sprite.getPosition().x + plateforme5Sprite.getGlobalBounds().width,
                                     900);
    plateforme6Sprite.setPosition(plateforme6Position);

    // Chargement de la première plateforme
    sf::Texture plateforme7Texture;
    if (!plateforme6Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme7Sprite(plateforme1Texture);
    sf::Vector2f plateforme7Position(plateforme6Sprite.getPosition().x + plateforme6Sprite.getGlobalBounds().width,
                                     900);
    plateforme7Sprite.setPosition(plateforme7Position);

    // Chargement de la première plateforme
    sf::Texture plateforme8Texture;
    if (!plateforme1Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme8Sprite(plateforme1Texture);
    sf::Vector2f plateforme8Position(plateforme7Sprite.getPosition().x + plateforme7Sprite.getGlobalBounds().width,
                                     900);
    plateforme8Sprite.setPosition(plateforme8Position);

    // Chargement de la première plateforme
    sf::Texture plateforme9Texture;
    if (!plateforme1Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite plateforme9Sprite(plateforme1Texture);
    sf::Vector2f plateforme9Position(plateforme8Sprite.getPosition().x + plateforme8Sprite.getGlobalBounds().width,
                                     900);
    plateforme9Sprite.setPosition(plateforme9Position);

    // Chargement de la première plateforme
    sf::Texture plateforme10Texture;
    if (!plateforme10Texture.loadFromFile("src/assets/platforme1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite plateforme10Sprite(plateforme1Texture);
    sf::Vector2f plateforme10Position(plateforme9Sprite.getPosition().x + plateforme9Sprite.getGlobalBounds().width,
                                      900);
    plateforme10Sprite.setPosition(plateforme10Position);


    // Chargement de la zone de fin
    sf::Texture finishTexture;
    if (!finishTexture.loadFromFile("src/assets/finish.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite finishSprite(finishTexture);
    sf::Vector2f finishSpritePosition(
        plateforme10Sprite.getPosition().x + (plateforme10Sprite.getGlobalBounds().width / 2),
        335);
    finishSprite.setPosition(finishSpritePosition);

    float parallaxOffset = 0.0f;

    sf::Time deltaTime = clock.restart();

    while (window->isOpen())
    {
        GameInputs(window, playerSprite, deltaTime, parallaxOffset);
        GamePhysics(playerSprite, deltaTime, plateforme1Sprite,
                    plateforme2Sprite, plateforme3Sprite, plateforme4Sprite, plateforme5Sprite, plateforme6Sprite,
                    plateforme7Sprite, plateforme8Sprite, plateforme9Sprite, plateforme10Sprite, finishSprite);

        GameDrawing(window, playerSprite, carte1Sprite, carte2Sprite, carte3Sprite, carte4Sprite, carte5Sprite,
                    carte6Sprite, carte7Sprite, carte8Sprite, carte9Sprite, carte10Sprite, plateforme1Sprite,
                    plateforme2Sprite, plateforme3Sprite, plateforme4Sprite, plateforme5Sprite, plateforme6Sprite,
                    plateforme7Sprite, plateforme8Sprite, plateforme9Sprite, plateforme10Sprite, finishSprite,
                    parallaxOffset);

        std::cout << plateforme4Sprite.getGlobalBounds().width;

        deltaTime = clock.restart();
    }


    return 0;
}
