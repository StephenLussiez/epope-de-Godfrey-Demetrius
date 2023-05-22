#pragma once
#include "Sprite.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

class ImgButton : public Sprite
{
public:
	ImgButton(std::string path, int width, int height);
	ImgButton(std::string path, sf::IntRect area);
	ImgButton(std::string path, int width, int height, sf::Vector2f pos);
	ImgButton(std::string path, sf::IntRect area, sf::Vector2f pos);
	bool IsClicked(sf::Vector2f click);
};
