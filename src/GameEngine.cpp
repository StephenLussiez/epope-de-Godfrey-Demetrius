#include "headers/GameEngine.h"
#include <iostream>
#include <SFML/Audio.hpp>// Inclure la bibliothèque SFML Audio
#include "headers/WindowManager.h"

GameEngine::GameEngine() {}

void GameEngine::GameInputs(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Time& deltaTime,
                            float& limitTimeJump, bool& canPressLeft, bool& canPressRight, float& parallaxOffset)
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
        playerSprite.move(0, jumpSpeed * 200 * deltaTimeSeconds);
        jumpHeightRemaining -= jumpSpeed;

        if (isJumping)
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
                             sf::Sprite& plateforme9Sprite, sf::Sprite& plateforme10Sprite, sf::Sprite& obstacle1Sprite,
                             sf::Sprite& obstacle2Sprite, sf::Sprite& enemy1Sprite, sf::Sprite& enemy2Sprite,
                             sf::Sprite& enemy3Sprite, sf::Sprite& finishSprite,
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
    obstacle1Sprite.move((parallaxOffset * 0.1f), 0);
    obstacle2Sprite.move((parallaxOffset * 0.1f), 0);
    enemy1Sprite.move((parallaxOffset * 0.1f), 0);
    enemy2Sprite.move((parallaxOffset * 0.1f), 0);
    enemy3Sprite.move((parallaxOffset * 0.1f), 0);
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
    window->draw(obstacle1Sprite);
    window->draw(obstacle2Sprite);
    window->draw(enemy1Sprite);
    window->draw(enemy2Sprite);
    window->draw(enemy3Sprite);
    window->draw(finishSprite);
    window->display();
}


bool GameEngine::CheckCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    return bounds1.intersects(bounds2);
}

bool GameEngine::IsPlayerAboveEnemy(const sf::Sprite& playerSprite, const sf::Sprite& enemySprite)
{
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    sf::FloatRect enemyBounds = enemySprite.getGlobalBounds();

    // Vérifie si le bas du joueur est au-dessus du haut de l'ennemi
    return playerBounds.top + playerBounds.height < enemyBounds.top + 5;
}

bool GameEngine::IsPlayerOnTheRight(const sf::Sprite& playerSprite, const sf::Sprite& sprite)
{
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    // Vérifie si le bas du joueur est au-dessus du haut de l'ennemi
    return playerSprite.getPosition().x + playerBounds.width > sprite.getPosition().x + spriteBounds.width + 5;
}

bool GameEngine::IsPlayerOnTheLeft(const sf::Sprite& playerSprite, const sf::Sprite& sprite)
{
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    // Vérifie si le bas du joueur est au-dessus du haut de l'ennemi
    return playerSprite.getPosition().x + playerBounds.width < sprite.getPosition().x + 10;
}

void GameEngine::GamePhysics(sf::RenderWindow* window, sf::Sprite& playerSprite, sf::Time deltaTime,
                             sf::Sprite& plateformSprite1,
                             sf::Sprite& plateforme2Sprite,
                             sf::Sprite& plateforme3Sprite, sf::Sprite& plateforme4Sprite,
                             sf::Sprite& plateforme5Sprite, sf::Sprite& plateforme6Sprite,
                             sf::Sprite& plateforme7Sprite, sf::Sprite& plateforme8Sprite,
                             sf::Sprite& plateforme9Sprite, sf::Sprite& plateforme10Sprite, sf::Sprite& obstacle1Sprite,
                             sf::Sprite& obstacle2Sprite, sf::Sprite& enemy1Sprite, sf::Sprite& enemy2Sprite,
                             sf::Sprite& enemy3Sprite, sf::Sprite& finishSprite, float& limitTimeJump,
                             bool& canPressLeft, bool& canPressRight,
                             float& parallaxOffset)
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
        CheckCollision(playerSprite, plateforme9Sprite) || CheckCollision(playerSprite, plateforme10Sprite) ||
        CheckCollision(playerSprite, obstacle1Sprite) || CheckCollision(playerSprite, obstacle2Sprite))
    {
        playerSprite.move(0, 0);
        limitTimeJump = 0.0f;
        //enemySprite.move(0, speed);
    } else
    {
        playerSprite.move(0, (speed + speed * deltaTimeSeconds));
    }


    if (CheckCollision(playerSprite, obstacle1Sprite))
    {
        if (IsPlayerAboveEnemy(playerSprite, obstacle1Sprite))
        {
            canPressLeft = true;
            canPressRight = true;
        } else if (IsPlayerOnTheRight(playerSprite, obstacle1Sprite))
        {
            canPressLeft = false;
        } else if (IsPlayerOnTheLeft(playerSprite, obstacle1Sprite))
        {
            canPressRight = false;
        }
    }

    if (CheckCollision(playerSprite, obstacle2Sprite))
    {
        if (IsPlayerAboveEnemy(playerSprite, obstacle2Sprite))
        {
            canPressLeft = true;
            canPressRight = true;
        } else if (IsPlayerOnTheRight(playerSprite, obstacle2Sprite))
        {
            canPressLeft = false;
        } else if (IsPlayerOnTheLeft(playerSprite, obstacle2Sprite))
        {
            canPressRight = false;
        }
    }


    // Vérification de la collision avec les ennemis
    if (CheckCollision(playerSprite, enemy1Sprite))
    {
        if (IsPlayerAboveEnemy(playerSprite, enemy1Sprite))
        {
            std::cout << "il est mort";
            // Le joueur a sauté au-dessus de l'ennemi, supprimez enemy1Sprite
            enemy1Sprite.setPosition(-1000, -1000); // Déplacez l'ennemi en dehors de l'écran
        } else
        {
            // Le joueur est entré en collision avec un ennemi, faites quelque chose (par exemple, affichez un message ou réinitialisez le niveau)
        }
    } else if (CheckCollision(playerSprite, enemy2Sprite))
    {
        if (IsPlayerAboveEnemy(playerSprite, enemy2Sprite))
        {
            std::cout << "il est mort";
            // Le joueur a sauté au-dessus de l'ennemi, supprimez enemy1Sprite
            enemy2Sprite.setPosition(-1000, -1000); // Déplacez l'ennemi en dehors de l'écran
        } else
        {
            // Le joueur est entré en collision avec un ennemi, faites quelque chose (par exemple, affichez un message ou réinitialisez le niveau)
        }
    } else if (CheckCollision(playerSprite, enemy3Sprite))
    {
        if (IsPlayerAboveEnemy(playerSprite, enemy3Sprite))
        {
            std::cout << "il est mort";
            // Le joueur a sauté au-dessus de l'ennemi, supprimez enemy1Sprite
            enemy3Sprite.setPosition(-1000, -1000); // Déplacez l'ennemi en dehors de l'écran
        } else
        {
            // Le joueur est entré en collision avec un ennemi, faites quelque chose (par exemple, affichez un message ou réinitialisez le niveau)
        }
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
    float limitTimeJump = 0.0f;
    bool canPressLeft = true;
    bool canPressRight = true;

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
    sf::Vector2f plateforme2Position(plateforme1Sprite.getGlobalBounds().width + 200, 900);
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
    sf::Vector2f plateforme4Position(
        plateforme3Sprite.getPosition().x + plateforme3Sprite.getGlobalBounds().width + 200,
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
    sf::Vector2f plateforme7Position(
        plateforme6Sprite.getPosition().x + plateforme6Sprite.getGlobalBounds().width + 200,
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
    sf::Vector2f plateforme9Position(
        plateforme8Sprite.getPosition().x + plateforme8Sprite.getGlobalBounds().width + 250,
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

    // Chargement d'un obstacle
    sf::Texture obstacle1Texture;
    if (!obstacle1Texture.loadFromFile("src/assets/obstacle1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite obstacle1Sprite(obstacle1Texture);
    sf::Vector2f obstacle1Position(plateforme5Sprite.getPosition().x + (plateforme5Sprite.getGlobalBounds().width / 3),
                                   645);
    obstacle1Sprite.setPosition(obstacle1Position);


    // Chargement d'un obstacle
    sf::Texture obstacle2Texture;
    if (!obstacle2Texture.loadFromFile("src/assets/obstacle1.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }


    sf::Sprite obstacle2Sprite(obstacle2Texture);
    sf::Vector2f obstacle2Position(plateforme8Sprite.getPosition().x + (plateforme8Sprite.getGlobalBounds().width / 3),
                                   645);
    obstacle2Sprite.setPosition(obstacle2Position);

    // Chargement d'un ennemi
    sf::Texture enemy1Texture;
    if (!enemy1Texture.loadFromFile("src/assets/monsterIdle.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite enemy1Sprite(enemy1Texture);
    sf::Vector2f enemy1Position(plateforme2Sprite.getPosition().x + (plateforme2Sprite.getGlobalBounds().width),
                                800);
    enemy1Sprite.setPosition(enemy1Position);

    // Chargement d'un ennemi
    sf::Texture enemy2Texture;
    if (!enemy2Texture.loadFromFile("src/assets/monsterIdle.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite enemy2Sprite(enemy2Texture);
    sf::Vector2f enemy2Position(plateforme6Sprite.getPosition().x + (plateforme6Sprite.getGlobalBounds().width),
                                800);
    enemy2Sprite.setPosition(enemy2Position);

    // Chargement d'un ennemi
    sf::Texture enemy3Texture;
    if (!enemy3Texture.loadFromFile("src/assets/monsterIdle.png"))
    {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }

    sf::Sprite enemy3Sprite(enemy3Texture);
    sf::Vector2f enemy3Position(plateforme9Sprite.getPosition().x + (plateforme9Sprite.getGlobalBounds().width + 50),
                                800);
    enemy3Sprite.setPosition(enemy3Position);

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

    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("src/EpicMusic.ogg")) { }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(100.0f);
    sound.play();


    sf::Time deltaTime = clock.restart();

    while (window->isOpen())
    {
        GamePhysics(window, playerSprite, deltaTime, plateforme1Sprite,
                    plateforme2Sprite, plateforme3Sprite, plateforme4Sprite, plateforme5Sprite, plateforme6Sprite,
                    plateforme7Sprite, plateforme8Sprite, plateforme9Sprite, plateforme10Sprite, obstacle1Sprite,
                    obstacle2Sprite, enemy1Sprite, enemy2Sprite, enemy3Sprite,
                    finishSprite, limitTimeJump, canPressLeft, canPressRight, parallaxOffset);
        GameInputs(window, playerSprite, deltaTime, limitTimeJump, canPressLeft, canPressRight, parallaxOffset);
        GameDrawing(window, playerSprite, carte1Sprite, carte2Sprite, carte3Sprite, carte4Sprite, carte5Sprite,
                    carte6Sprite, carte7Sprite, carte8Sprite, carte9Sprite, carte10Sprite, plateforme1Sprite,
                    plateforme2Sprite, plateforme3Sprite, plateforme4Sprite, plateforme5Sprite, plateforme6Sprite,
                    plateforme7Sprite, plateforme8Sprite, plateforme9Sprite, plateforme10Sprite, obstacle1Sprite,
                    obstacle2Sprite, enemy1Sprite, enemy2Sprite, enemy3Sprite,
                    finishSprite,
                    parallaxOffset);


        deltaTime = clock.restart();
    }

    return 0;
}
