#pragma once
#include <SFML/Graphics.hpp>

class DrawableEntity : public sf::Drawable, public sf::Transformable
{
public:
	DrawableEntity();
	~DrawableEntity();

	// Renvoit le centre de l'entité et pas le coin en haut à gauche
	virtual sf::Vector2f getPosition() const;

	sf::Sprite getSprite() const;

	/* Orientation de l'entite vers la position */
	void orientate(const sf::Vector2f& position);

	sf::FloatRect getGlobalBounds();

	std::vector<sf::Vector2f> getCorners();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite _sprite;
};

