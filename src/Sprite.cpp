#include "headers/Sprite.h"

void Sprite::set_Texture(std::string path)
{
	m_texture.loadFromFile(path);
	m_sprite.setTexture(m_texture);
}
void Sprite::set_Texture(std::string path, sf::IntRect area)
{
	m_texture.loadFromFile(path, area);
	m_sprite.setTexture(m_texture);
}

void Sprite::set_Dimensions(int top, int left, int width, int height)
{
	m_dimensions.top = top;
	m_dimensions.left = left;
	m_dimensions.width = width;
	m_dimensions.height = height;
	m_sprite.setTextureRect(m_dimensions);
}

void Sprite::set_Dimensions(sf::IntRect rect)
{
	m_dimensions = rect;
}


void Sprite::set_Position(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void Sprite::set_maxSize(int size)
{
	maxSize = size;
}

sf::Texture Sprite::get_texture()
{
	return (m_texture);
}

sf::Vector2f Sprite::get_position()
{
	return (m_position);
}


sf::IntRect Sprite::get_dimensions()
{
	return (m_dimensions);
}

sf::Sprite Sprite::get_sprite()
{
	return (m_sprite);
}

Sprite::Sprite(std::string path)
{
	set_Texture(path);
}

Sprite::Sprite(std::string path, sf::IntRect area)
{
	set_Texture(path, area);
}

Sprite::Sprite(std::string path, sf::Vector2f pos)
{
	set_Texture(path);
	set_Position(pos);
}

Sprite::Sprite(std::string path, sf::IntRect area, sf::Vector2f pos)
{
	set_Texture(path, area);
	set_Position(pos);
}

void Sprite::animate()
{
	m_dimensions.top += m_dimensions.width;
	if (m_dimensions.top > maxSize)
		m_dimensions.top = 0;
}

void Sprite::Draw(sf::RenderWindow window)
{
	window.draw(m_sprite);
}