#include <SFML/Graphics/Sprite.hpp>;
#include <SFML/Graphics/Texture.hpp>;
#include <SFML/System/Vector2.hpp>;
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <string>;

class Sprite
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;

public:
	Sprite(std::string path);
	Sprite(std::string path, sf::IntRect area);
	Sprite(std::string path, sf::Vector2f pos);
	Sprite(std::string path, sf::IntRect area, sf::Vector2f pos);
	void setTexture(std::string path);
	void setTexture(std::string path, sf::IntRect);
	void setPosition(sf::Vector2f pos);
	sf::Texture get_texture();
	sf::Vector2f get_position();
	sf::Sprite get_sprite();
	void Draw(sf::RenderWindow window);
};
