#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!"
		"\n\nPress [SPACE] to retry"
		"\n\nPress [ESC] to quit");
	text_.setColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		Game::Screen = std::make_shared<GameScreen>();	
		bgTable_ = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		bgColor_ = sf::Color(227,202,168);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		bgColor_ = sf::Color::Black;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		bgColor_ = sf::Color(139, 69, 19);
	}
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
}