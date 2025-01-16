#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

extern sf::Vector2i flag;

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down
	};

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window, std::vector<Fruit>& fruits);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;

	unsigned getSize() const;
	
	void knn(std::vector<Fruit>& fruits);

	float getAngleBetweenVectors(const sf::Vector2f& v1, const sf::Vector2f& v2);

private:
	void move();
	void grow();
	void more_grow();
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

	sf::Vector2f position_;
	// Direction direction_;
	sf::Vector2f my_direction;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	sf::Texture headTexture;

	SnakeHead snake_head;

	std::vector<SnakeNode> nodes_;

	static const int InitialSize;
};
}

#endif