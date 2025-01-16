#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include "Screen.h"

extern sf::Color bgColor_;
extern int bgTable_;

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();
	// sf::Color setColor(sf::Color color);
	// const sf::Color getColor();
	const sf::RenderWindow& getWindow();

	static const int Width = 640*3;
	static const int Height = 480*3;

	static std::shared_ptr<Screen> Screen;

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	// sf::Color bgColor_;

	static const sf::Time TimePerFrame;
};
}


#endif