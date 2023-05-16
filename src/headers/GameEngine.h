#include <SFML/Graphics.hpp>

class GameEngine {

public:
	GameEngine();
	int Gameloop();
	void GameInputs(sf::RenderWindow* window);
	void GameDrawing(sf::RenderWindow* window);
};