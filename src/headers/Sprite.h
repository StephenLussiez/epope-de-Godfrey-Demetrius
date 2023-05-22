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
	sf::Vector2f m_size;
	// Pour les animations
	sf::IntRect m_area;
	int maxSize;
	sf::Sprite m_sprite;

public:
	Sprite(std::string path, int width, int height);
	Sprite(std::string path, sf::IntRect area);
	Sprite(std::string path, int width, int height, sf::Vector2f pos);
	Sprite(std::string path, sf::IntRect area, sf::Vector2f pos);

	void set_texture(std::string path);
	void set_area(int top, int left, int width, int height);
	void set_area(sf::IntRect rect);
	void set_size(int width, int height);
	void set_size(sf::Vector2f size);
	void set_position(float x, float y);
	void set_position(sf::Vector2f pos);
	void set_maxSize(int size);

	sf::Texture get_texture();
	sf::Vector2f get_position();
	sf::Vector2f get_size();
	sf::IntRect get_area();
	sf::Sprite get_sprite();

	void animate();
	void Draw(sf::RenderWindow window);
};
