#include "headers/GameEngine.h"
#include <iostream>
#include "headers/WindowManager.h"

GameEngine::GameEngine() {}

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
}

void GameEngine::GameDrawing(sf::RenderWindow* window)
{
    sf::Texture fondTexture;
    if (!fondTexture.loadFromFile("Carte1.png")) {
        // G�rer l'erreur si la texture ne peut pas �tre charg�e
    }
    sf::Sprite fondSprite(fondTexture);

    sf::Texture carteTexture;
    if (!carteTexture.loadFromFile("Carte1.png")) {
        // G�rer l'erreur si la texture ne peut pas �tre charg�e
    }
    sf::Sprite carteSprite(carteTexture);
    sf::Vector2f cartePosition(-static_cast<float>(carteTexture.getSize().x), 0); // Position initiale � gauche de l'�cran
    carteSprite.setPosition(cartePosition);

    const float vitesseCarte = 5.0f; // Vitesse de d�placement de la carte
    const float largeurFenetre = 800.0f; // Largeur de la fen�tre de jeu

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        cartePosition.x += vitesseCarte; // D�placement vers la droite
        if (cartePosition.x >= largeurFenetre) {
            // La carte a atteint la fin de l'�cran, changer la texture du fond
            if (!fondTexture.loadFromFile("Carte2.png")) {
                // G�rer l'erreur si la texture ne peut pas �tre charg�e
            }
            cartePosition.x = -static_cast<float>(carteTexture.getSize().x); // R�initialiser la position de la carte � gauche de l'�cran
        }
    }
    carteSprite.setPosition(cartePosition); // Mettre � jour la position de la carte

    window->clear();
    window->draw(fondSprite);
    window->draw(carteSprite);
    window->display();
}

int GameEngine::Gameloop()
{
    WindowManager* windowBox = new WindowManager();
    sf::RenderWindow* window = windowBox->CreateWindow(1920, 1080, "L'�pop�e de Goldfey Dimitrius");

    while (window->isOpen()) {
        GameInputs(window);
        GameDrawing(window);
    }
    return (0);
}