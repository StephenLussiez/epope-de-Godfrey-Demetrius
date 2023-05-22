#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFMl/System/Vector2.hpp"

class Rectangle
{
private:
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Color m_color;
	sf::RectangleShape m_shape;

public:
	Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color color);
	void setSize(sf::Vector2f size);
	void setColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getSize();
	sf::Color getColor();
	sf::Vector2f getPosition();
};