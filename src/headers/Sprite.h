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
	// Pour les animations
	sf::IntRect m_dimensions;
	int maxSize;
public:
	Sprite(std::string path);
	Sprite(std::string path, sf::IntRect area);
	Sprite(std::string path, sf::Vector2f pos);
	Sprite(std::string path, sf::IntRect area, sf::Vector2f pos);

	void set_Texture(std::string path);
	void set_Dimensions(int top, int left, int width, int height);
	void set_Dimensions(sf::IntRect rect);
	void set_Texture(std::string path, sf::IntRect);
	void set_Position(sf::Vector2f pos);
	void set_maxSize(int size);

	sf::Texture get_texture();
	sf::Vector2f get_position();
	sf::IntRect get_dimensions();
	sf::Sprite get_sprite();

	void animate();
	void Draw(sf::RenderWindow window);
};
