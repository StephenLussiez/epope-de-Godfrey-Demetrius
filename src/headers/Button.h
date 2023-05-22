#pragma once
#include "Rectangle.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>


class Button : public Rectangle
{
public:
	Button(sf::Vector2f size, sf::Vector2f pos, sf::Color color);
	bool IsClicked(sf::Vector2f click);
};

