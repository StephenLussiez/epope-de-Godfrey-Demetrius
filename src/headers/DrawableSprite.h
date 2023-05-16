#include <SFML/Graphics/Drawable.hpp>;
#include <SFML/Graphics/RenderTarget.hpp>;
#include <SFML/Graphics/Sprite.hpp>;
#include <SFML/Graphics/Texture.hpp>;

#include <format>;
#include <memory>;
#include <string>;

class DrawableSprite final : public sf::Drawable
{
public:
    /**
     * \brief crée une image à partir d'un fichier
     * \param file_path correspond au chemin vers le fichier qui sera utilisé
     */
    explicit DrawableSprite(const std::string& file_path);
    DrawableSprite() = default;

    DrawableSprite(const DrawableSprite& other);
    //DrawableSprite(const DrawableSprite& _Sprite);

    /**
     * \brief crée un image à partir d'une texture chargé dans la mémoire
     * \param texture est un share pointer pour chaque texture utilisé
     */
    explicit DrawableSprite(const std::shared_ptr<sf::Texture> texture);
    ~DrawableSprite() override = default;
    /**
     * \return la position de l'image depuis en haut à gauche de l'écran
     */
    const sf::Vector2f& position() const noexcept { return m_sprite->getPosition(); }
    /**
     * \return le facteur de taille
     */
    const sf::Vector2f& scale() const noexcept { return m_sprite->getScale(); }
    /**
     * \return les rebords rectangulaires de l'image
     */
    sf::FloatRect globalBounds() const noexcept { return m_sprite->getGlobalBounds(); }
    /**
     * \return la texture sous-jacente de SFML
     */
    const sf::Texture& texture() const noexcept { return *m_sprite->getTexture(); }
    /**
     * \return le sprite sous-jacent de SFML
     */
    const sf::Sprite& sprite() const noexcept { return *m_sprite; }
    /**
     * \return L'origin de l'image
     */
    sf::Vector2f origin() const noexcept { return m_sprite->getOrigin(); }
    /**
     * \brief Bouge l'image à la position donnée
     * \param position correspond à la nouvelle position de l'image
     */
    void setPosition(const sf::Vector2f& position) noexcept { m_sprite->setPosition(position); }
    /**
     * \brief tourne l'image dans un angle donné
     * \param angle correspond à l'angle en degré
     */
    void setRotation(const float& angle) noexcept { m_sprite->setRotation(angle); }
    /**
     * brief la taille de l'image par un facteur donné
     * \param scale correspond au nouveau facteur de la taille de l'image
     */
    void setScale(const sf::Vector2f& scale) noexcept { m_sprite->setScale(scale); }
    /**
     * \brief configure l'origine de l'image
     * \param origin correspond à l'origine de l'image
     */
    void setOrigin(const sf::Vector2f& origin) noexcept { m_sprite->setOrigin(origin); }
    /**
     * \brief Dessine l'image sur une cible
     * \param target correspond à la cible où l'image sera dessiné
     * \param states correspond aux états utilisé pour le rendu de l'image
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::shared_ptr<sf::Texture> m_texture;
    std::unique_ptr<sf::Sprite> m_sprite;
};
