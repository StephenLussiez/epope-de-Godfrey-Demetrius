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
	void set_size(sf::Vector2f size);
	void set_color(sf::Color color);
	void set_position(sf::Vector2f pos);
	sf::Vector2f get_size();
	sf::Color get_color();
	sf::Vector2f get_position();
};