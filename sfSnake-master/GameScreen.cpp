#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <string.h>
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "Snake.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		Game::Screen = std::make_shared<GameScreen>();	
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
		bgTable_ = -bgTable_;
	}
	else{
		snake_.handleInput(window, fruit_);
	}
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() <= 5)//TODO
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf()){
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
		bgTable_ = -1;
	}
		
}

void GameScreen::render(sf::RenderWindow& window)
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	std::string button1, button2;
	if(bgTable_==1){
		button1 = "ON";
	}
	else{
		button1 = "OFF";
	}
	if(flag.x==1){
		button2 = "ON";
	}
	else{
		button2 = "OFF";
	}
	text_.setString(
		"Press [F] to use/disable grids: " + button1 + " \n\nPress [G] to use AI: " + button2);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 10);

	window.draw(text_);
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

// void GameScreen::generateFruit()
// {
// 	static std::default_random_engine engine;
// 	engine.seed(time(NULL));
// 	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
// 	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

// 	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
// }

void GameScreen::generateFruit()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
    static std::uniform_real_distribution<float> colorDistribution(0.f, 1.f);
    static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
    static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

    float randomValue = colorDistribution(engine);
    sf::Color color;

    if (randomValue < 0.25f) {
        // 25% 的概率生成黑色水果
        color = sf::Color::Black;
    } else if (randomValue < 0.5f) {
        // 25% 的概率生成棕色水果
        color = sf::Color(139, 69, 19); 
    } else if (randomValue < 0.75f) {
        // 25% 的概率生成红色水果
        color = sf::Color::Red;
    } else if (randomValue < 0.875f) {
        // 12.5% 的概率生成蓝色水果
        color = sf::Color::Blue;
    } else {
        // 12.5% 的概率生成绿色水果
        color = sf::Color::Green;
    }

    fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), color));
}
