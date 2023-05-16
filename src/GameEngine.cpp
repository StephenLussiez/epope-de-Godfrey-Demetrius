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
        // Gérer l'erreur si la texture ne peut pas être chargée
    }
    sf::Sprite fondSprite(fondTexture);

    sf::Texture carteTexture;
    if (!carteTexture.loadFromFile("Carte1.png")) {
        // Gérer l'erreur si la texture ne peut pas être chargée
    }
    sf::Sprite carteSprite(carteTexture);
    sf::Vector2f cartePosition(-static_cast<float>(carteTexture.getSize().x), 0); // Position initiale à gauche de l'écran
    carteSprite.setPosition(cartePosition);

    const float vitesseCarte = 5.0f; // Vitesse de déplacement de la carte
    const float largeurFenetre = 800.0f; // Largeur de la fenêtre de jeu

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        cartePosition.x += vitesseCarte; // Déplacement vers la droite
        if (cartePosition.x >= largeurFenetre) {
            // La carte a atteint la fin de l'écran, changer la texture du fond
            if (!fondTexture.loadFromFile("Carte2.png")) {
                // Gérer l'erreur si la texture ne peut pas être chargée
            }
            cartePosition.x = -static_cast<float>(carteTexture.getSize().x); // Réinitialiser la position de la carte à gauche de l'écran
        }
    }
    carteSprite.setPosition(cartePosition); // Mettre à jour la position de la carte

    window->clear();
    window->draw(fondSprite);
    window->draw(carteSprite);
    window->display();
}

int GameEngine::Gameloop()
{
    WindowManager* windowBox = new WindowManager();
    sf::RenderWindow* window = windowBox->CreateWindow(1920, 1080, "L'épopée de Goldfey Dimitrius");

    while (window->isOpen()) {
        GameInputs(window);
        GameDrawing(window);
    }
    return (0);
}