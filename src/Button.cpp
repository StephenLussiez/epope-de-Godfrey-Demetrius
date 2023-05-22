#include "headers/Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
{
	m_button = new Rectangle(size, pos, color);
}

bool IsClicked(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f click)
{
	if (click.x > pos.x && click.x < pos.x - size.x)
		if (click.y > pos.y && click.y < pos.y + size.y)
			return (true);
	return (false);
}