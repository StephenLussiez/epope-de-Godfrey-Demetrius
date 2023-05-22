#include "headers/Rectangle.h"

void Rectangle::setSize(sf::Vector2f size)
{
	m_size = size;
	m_shape.setSize(size);
}
void Rectangle::setColor(sf::Color color)
{
	m_color = color;
	m_shape.setFillColor(color);
}
void Rectangle::setPosition(sf::Vector2f pos)
{
	m_position = pos;
	setPosition(pos);
}

sf::Vector2f Rectangle::getSize()
{
	return (m_size);
}

sf::Color Rectangle::getColor()
{
	return (m_color);
}

sf::Vector2f Rectangle::getPosition()
{
	return (m_position);
}

Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
{
	setSize(size);
	setPosition(pos);
	setColor(color);
}

