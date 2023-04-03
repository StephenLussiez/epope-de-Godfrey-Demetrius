#include "managers/GameEngine.h"
#include "managers/WindowManager.h"
#include <iostream>

GameEngine::GameEngine()
{

}

int GameEngine::Gameloop()
{
	WindowManager* windowBox = new WindowManager();
	sf::RenderWindow* window = windowBox->CreateWindow(1920, 1080, "L'épopée de Goldfey Dimitrius");
	sf::Event event;
	
	while (window->isOpen()) {
		if (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}
	}
	return (0);
}