#pragma once
#include <SFML/Graphics.hpp>

class WindowManager {
	static WindowManager* m_instance;
	int m_width;
	int m_height;
	std::string m_name;


public:
	static WindowManager* GetInstance();
	WindowManager();
	sf::RenderWindow* CreateWindow(int width, int height, std::string name);
	sf::RenderWindow* GetWindow();
	int GetWidth();
	int GetHeight();
	std::string GetName();
};