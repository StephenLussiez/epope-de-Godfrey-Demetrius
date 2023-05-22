#include "headers/Rectangle.h"

void Rectangle::set_size(sf::Vector2f size)
{
	m_size = size;
	m_shape.setSize(size);
}
void Rectangle::set_color(sf::Color color)
{
	m_color = color;
	m_shape.setFillColor(color);
}
void Rectangle::set_position(sf::Vector2f pos)
{
	m_position = pos;
	set_position(pos);
}

sf::Vector2f Rectangle::get_size()
{
	return (m_size);
}

sf::Color Rectangle::get_color()
{
	return (m_color);
}

sf::Vector2f Rectangle::get_position()
{
	return (m_position);
}

Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
{
	set_size(size);
	set_position(pos);
	set_color(color);
}

