#include "DrawableSprite.h"


DrawableSprite::DrawableSprite(const std::string& file_path)
{
    m_texture = std::make_shared<sf::Texture>();
    m_texture->loadFromFile(file_path);
    m_sprite = std::make_unique<sf::Sprite>(*m_texture);
}

DrawableSprite::DrawableSprite(const DrawableSprite& other)
    : m_texture(other.m_texture)
{
    m_sprite = std::make_unique<sf::Sprite>(*m_texture);
}

DrawableSprite::DrawableSprite(const std::shared_ptr<sf::Texture> texture)
    : m_texture(texture)
{
    m_sprite = std::make_unique<sf::Sprite>(*m_texture);
}

void DrawableSprite::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(*m_sprite);
}
