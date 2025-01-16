#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0), sf::Color color = sf::Color::Red);

	void render(sf::RenderWindow& window);

	const sf::Color getColor();

	sf::FloatRect getBounds() const;

	sf::Vector2f getPosition();
private:
	sf::CircleShape shape_;
	sf::Color color_;

	static const float Radius;
};
}

#endif