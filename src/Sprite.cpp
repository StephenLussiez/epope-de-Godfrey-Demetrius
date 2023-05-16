#include "headers/Sprite.h"

void Sprite::setTexture(std::string path)
{
	m_texture.loadFromFile(path);
	m_sprite.setTexture(m_texture);
}
void Sprite::setTexture(std::string path, sf::IntRect area)
{
	m_texture.loadFromFile(path, area);
	m_sprite.setTexture(m_texture);
}

void Sprite::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

sf::Texture Sprite::get_texture()
{
	return (m_texture);
}

sf::Vector2f Sprite::get_position()
{
	return (m_position);
}

sf::Sprite Sprite::get_sprite()
{
	return (m_sprite);
}

Sprite::Sprite(std::string path)
{
	setTexture(path);
}

Sprite::Sprite(std::string path)
{
	setTexture(path);
}

Sprite::Sprite(std::string path, sf::IntRect area)
{
	setTexture(path, area);
}

Sprite::Sprite(std::string path, sf::Vector2f pos)
{
	setTexture(path);
	setPosition(pos);
}

Sprite::Sprite(std::string path, sf::IntRect area, sf::Vector2f pos)
{
	setTexture(path, area);
	setPosition(pos);
}

void Sprite::Draw(sf::RenderWindow window)
{
	window.draw(m_sprite);
}