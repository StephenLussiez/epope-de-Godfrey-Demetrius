#pragma once
#include "Sprite.h"
#include "headers/Rectangle.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>


class Button
{
private:
	Rectangle* m_button;

public:
	Button(sf::Vector2f size, sf::Vector2f pos, sf::Color color);
	bool IsClicked(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f click);
};

