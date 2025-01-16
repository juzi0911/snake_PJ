#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

sf::Color bgColor_ = sf::Color(227,202,168);
int bgTable_ = -1;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile("Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

// void Game::render()
// {
// 	window_.clear(bgColor_);
// 	Game::Screen->render(window_);
// 	window_.display();
// }


void Game::render()
{
	window_.clear(bgColor_);

	if(bgTable_==1){
		// Draw grid
		const int gridSize = 40;  // Adjust the grid size as needed
		const int cellSize = window_.getSize().x / gridSize;

		sf::Color gridColor(128, 128, 128);  // Adjust the grid color as needed

		sf::VertexArray gridLines(sf::Lines);

		// Draw vertical grid lines
		for (int x = 0; x <= window_.getSize().x; x += cellSize)
		{
			gridLines.append(sf::Vertex(sf::Vector2f(x, 0), gridColor));
			gridLines.append(sf::Vertex(sf::Vector2f(x, window_.getSize().y), gridColor));
		}

		// Draw horizontal grid lines
		for (int y = 0; y <= window_.getSize().y; y += cellSize)
		{
			gridLines.append(sf::Vertex(sf::Vector2f(0, y), gridColor));
			gridLines.append(sf::Vertex(sf::Vector2f(window_.getSize().x, y), gridColor));
		}

		// Set line thickness and style to achieve dashed line effect
		float lineThickness = 1.f;  // Adjust the line thickness as needed
		sf::Uint8 lineAlpha = 128;  // Adjust the line transparency as needed

		for (std::size_t i = 0; i < gridLines.getVertexCount(); i += 2)
		{
			sf::Vertex& vertex1 = gridLines[i];
			sf::Vertex& vertex2 = gridLines[i + 1];

			// Set line thickness
			vertex1.color.a = lineAlpha;
			vertex1.position += sf::Vector2f(lineThickness / 2.f, lineThickness / 2.f);
			vertex2.color.a = lineAlpha;
			vertex2.position += sf::Vector2f(lineThickness / 2.f, lineThickness / 2.f);
		}

		window_.draw(gridLines);
	}

	Game::Screen->render(window_);
	window_.display();
}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();

	}
}

// sf::Color Game::setColor(sf::Color color){
// 	bgColor_ = color;
// }

// const sf::Color Game::getColor(){
// 	return bgColor_;
// }

const sf::RenderWindow& Game::getWindow() {
	return window_;
}