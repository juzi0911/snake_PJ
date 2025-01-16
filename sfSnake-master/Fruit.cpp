#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position, sf::Color color)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(color);
	color_ = color;
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

const sf::Color Fruit::getColor(){
	return color_;
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f Fruit::getPosition(){
	return shape_.getPosition();
}