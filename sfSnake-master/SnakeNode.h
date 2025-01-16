#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setAngle(float angle);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
	float getAngle();
	sf::Vector2f cal_angle(sf::Vector2f position, float angle);

	static const float Width;
	static const float Height;
	static const float Radius;

private:
	sf::CircleShape shape_;
	sf::CircleShape coll;
	sf::RectangleShape deco_;
	sf::Vector2f position_;
	float angle_;
};

class SnakeHead {
public:
    SnakeHead(sf::Vector2f position = sf::Vector2f(0, 0), sf::Texture* texture = nullptr);

    void setTexture(sf::Texture* texture);
    void render(sf::RenderWindow& window);
	void move(float xOffset, float yOffset);
	sf::Vector2f getHeadPosition();
	float getHeadAngle();
	void setHeadPosition(sf::Vector2f position);
	void setHeadAngle(float angle);
	sf::FloatRect getBounds1() const;
	sf::FloatRect getBounds2() const;

private:
    sf::Sprite sprite_;
	sf::CircleShape head_coll;
	sf::Vector2f head_position;
	float head_angle;
};

}

#endif