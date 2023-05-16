#pragma once
#include "SFML/Graphics/RectangleShape.hpp"

class Rectangle
{
private:
	sf::IntRect m_dimensions;
	sf::Vector2f m_position;
	sf::Color color;
	sf::RectangleShape m_shape;

public:
	sf::IntRect area();
	sf::RectangleShape get_Button();
	void create_button();
	void setArea();
	void setposition();
};