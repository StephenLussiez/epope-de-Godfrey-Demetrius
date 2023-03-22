#include <SFML/Graphics.hpp>

class WindowManager {
	WindowManager* instance;
	int m_width;
	int m_height;
	std::string m_name;
	sf::RenderWindow* m_window;

public:
	WindowManager();
	sf::RenderWindow* CreateWindow(int width, int height, std::string name);
	sf::RenderWindow* GetWindow();
};