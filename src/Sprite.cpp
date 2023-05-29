#include "headers/Sprite.h"

void Sprite::set_texture(std::string path)
{
	m_texture.loadFromFile(path);
	m_sprite.setTexture(m_texture);
}

void Sprite::set_area(int top, int left, int width, int height)
{
	m_area.top = top;
	m_area.left = left;
	m_area.width = width;
	m_area.height = height;
	m_sprite.setTextureRect(m_area);
}

void Sprite::set_area(sf::IntRect rect)
{
	m_area = rect;
}

void Sprite::set_size(int width, int height)
{
	m_size.x = width;
	m_size.y = height;
}

void Sprite::set_size(sf::Vector2f size)
{
	m_size = size;
}

void Sprite::set_position(float x, float y)
{
	m_sprite.setPosition(sf::Vector2f{ x, y });
}

void Sprite::set_position(sf::Vector2f pos)
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

sf::Vector2f Sprite::get_size()
{
	return (m_size);
}

sf::Vector2f Sprite::get_position()
{
	return (m_sprite.getPosition());
}


sf::IntRect Sprite::get_area()
{
	return (m_area);
}

sf::Sprite Sprite::get_sprite()
{
	return (m_sprite);
}

sf::FloatRect Sprite::get_globalBounds()
{
	return (m_sprite.getGlobalBounds());
}

Sprite::Sprite(std::string path, int width, int height)
{
	set_texture(path);
	m_size.x = width;
	m_size.y = height;
}

Sprite::Sprite(std::string path, sf::IntRect area)
{
	set_texture(path);
	m_size.x = area.width;
	m_size.y = area.height;
	set_area(area);
}

Sprite::Sprite(std::string path, int width, int height, sf::Vector2f pos)
{
	set_texture(path);
	m_size.x = width;
	m_size.y = height;
	set_position(pos);
}

Sprite::Sprite(std::string path, sf::IntRect area, sf::Vector2f pos)
{
	set_texture(path);
	set_position(pos);
}

void Sprite::animate()
{
	m_area.top += m_area.width;
	if (m_area.top > maxSize)
		m_area.top = 0;
}

void Sprite::Draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void Sprite::Move(float x, float y)
{
	m_sprite.move(sf::Vector2f{ x, y });
}

void Sprite::Move(sf::Vector2f pos)
{
	m_sprite.move(pos);
}

bool Sprite::intersects(Sprite* other)
{
	return (this->get_globalBounds().intersects(other->get_globalBounds()));
}