#include "headers/ImgButton.h"

ImgButton::ImgButton(std::string path, int width, int height)
	: Sprite(path, width, height)  {}

ImgButton::ImgButton(std::string path, sf::IntRect area)
	: Sprite(path, area) {}

ImgButton::ImgButton(std::string path, int width, int height, sf::Vector2f pos)
	: Sprite(path, width, height, pos) {}

ImgButton::ImgButton(std::string path, sf::IntRect area, sf::Vector2f pos)
	: Sprite(path, area, pos) {}

bool ImgButton::IsClicked(sf::Vector2f click)
{
	sf::Vector2f pos = get_position();
	sf::Vector2f size = get_size();
	if (click.x > pos.x && click.x < pos.x - size.x)
		if (click.y > pos.y && click.y < pos.y + size.y)
			return (true);
	return (false);
}