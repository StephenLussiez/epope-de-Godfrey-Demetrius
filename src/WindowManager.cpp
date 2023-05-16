#include "headers/WindowManager.h"

WindowManager* WindowManager::m_instance = nullptr;

WindowManager* WindowManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new WindowManager();
	}

	return m_instance;
}

WindowManager::WindowManager()
{
	m_window = nullptr;
	m_width = 1920;
	m_height = 1080;
	m_name = "";
}

sf::RenderWindow* WindowManager::CreateWindow(int width = 1920, int height = 1080, std::string title = "L'épopée de Goldfey Dimitrius")
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	return (m_window);
}

sf::RenderWindow* WindowManager::GetWindow()
{
	return (m_window);
}

int WindowManager::GetWidth()
{
	return (m_width);
}

int WindowManager::GetHeight()
{
	return (m_height);
}

std::string WindowManager::GetName()
{
	return (m_name);
}