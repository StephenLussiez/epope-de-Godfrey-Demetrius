#include "headers/Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
	: Rectangle(size, pos, color) {}

bool Button::IsClicked(sf::Vector2f click)
{
	sf::Vector2f pos = get_position();
	sf::Vector2f size = get_size();
	if (click.x > pos.x && click.x < pos.x - size.x)
		if (click.y > pos.y && click.y < pos.y + size.y)
			return (true);
	return (false);
}