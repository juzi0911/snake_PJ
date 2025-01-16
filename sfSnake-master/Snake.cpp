#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>
#include <math.h>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;
sf::Vector2i flag = sf::Vector2i(-1, -1);
inline const int Snake::InitialSize = 5;
inline float Speed = 1.3 * SnakeNode::Radius;

Snake::Snake() : my_direction(sf::Vector2i(0, -Speed)), hitSelf_(false)
{
	headTexture.loadFromFile("Textures/snake_head.png");

	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

// void Snake::initNodes()
// {
// 	for (int i = 0; i < Snake::InitialSize; ++i)
//     {
//         nodes_.push_back(SnakeNode(sf::Vector2f(
//             Game::Width / 2,
//             Game::Height / 2 + 20*i)));
//     }
// }

void Snake::initNodes()
{
    snake_head = SnakeHead(sf::Vector2f(Game::Width / 2, Game::Height / 2), &headTexture);

    for (int i = 1; i < Snake::InitialSize; ++i)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(
            Game::Width / 2,
            Game::Height / 2 + Speed * i)));
    }
}

// void Snake::handleInput(sf::RenderWindow& window)
// {
// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
// 		my_direction = sf::Vector2f(0, -SnakeNode::Radius*2);
// 	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
// 		my_direction = sf::Vector2f(0, SnakeNode::Radius*2);
// 	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
// 		my_direction = sf::Vector2f(-SnakeNode::Radius*2, 0);
// 	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
// 		my_direction = sf::Vector2f(SnakeNode::Radius*2, 0);
// 	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
// 		my_direction = sf::Vector2f(sf::Mouse::getPosition(window).x - nodes_[0].getPosition().x, sf::Mouse::getPosition(window).y - nodes_[0].getPosition().y); 
// 		double temp = sqrt(my_direction.x * my_direction.x + my_direction.y * my_direction.y)/20;
// 		my_direction.x /= temp;
// 		my_direction.y /= temp;
// 		std::cout << my_direction.x << '\t' << my_direction.y << std::endl;
// 	}
// }

void Snake::handleInput(sf::RenderWindow& window, std::vector<Fruit>& fruits)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		my_direction = sf::Vector2f(0, -Speed);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		my_direction = sf::Vector2f(0, Speed);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		my_direction = sf::Vector2f(-Speed, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		my_direction = sf::Vector2f(Speed, 0);
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		my_direction = sf::Vector2f(sf::Mouse::getPosition(window).x - snake_head.getHeadPosition().x, sf::Mouse::getPosition(window).y - snake_head.getHeadPosition().y); 
		double distance = sqrt(pow(my_direction.x, 2) + pow(my_direction.y, 2))/Speed;
		my_direction.x /= distance;
		my_direction.y /= distance;
		// std::cout << my_direction.x << '\t' << my_direction.y << std::endl;
	}
	else{
		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
			flag.x = -flag.x;
			flag.y = 1;
		 }
		 if(flag.x == 1){
			// std::cout<<"flag.x:"<<flag.x<<std::endl;
			knn(fruits);
		 }

	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(snake_head.getBounds1())){
			toRemove = it;
		}
	}
	
	// if (toRemove != fruits.end())
	// {
	// 	pickupSound_.play();
	// 	grow();
	// 	fruits.erase(toRemove);
	// }

	if (toRemove != fruits.end())
    {
        pickupSound_.play();
		flag.y = 1;
		// std::cout<<"flag.y置为1"<<std::endl;
		sf::Color fruitColor = toRemove->getColor();

        if (fruitColor == sf::Color::Black || fruitColor == sf::Color(139, 69, 19))
        {
            // 黑色或棕色水果不增加长度
        }
        else if (fruitColor == sf::Color::Red)
        {
            // 红色水果增加长度 3 次
            grow();
            more_grow();
            more_grow();
        }
        else if (fruitColor == sf::Color::Blue)
        {
            // 蓝色水果增加长度 2 次
            grow();
            more_grow();
        }
        else if (fruitColor == sf::Color::Green)
        {
            // 绿色水果增加长度 1 次
            grow();
        }

        fruits.erase(toRemove);
    }


}

void Snake::grow()
{	
	SnakeNode snode;
	snode.setAngle(nodes_[nodes_.size() - 1].getAngle());
	snode.setPosition(sf::Vector2f(2*nodes_[nodes_.size() - 1].getPosition().x - nodes_[nodes_.size() - 2].getPosition().x, 
								   2*nodes_[nodes_.size() - 1].getPosition().y - nodes_[nodes_.size() - 2].getPosition().y));
	nodes_.push_back(snode);
	// switch (direction_)
	// {
	// case Direction::Up:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	// 		nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
	// 	break;
	// case Direction::Down:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	// 		nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
	// 	break;
	// case Direction::Left:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,
	// 		nodes_[nodes_.size() - 1].getPosition().y)));
	// 	break;
	// case Direction::Right:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,
	// 		nodes_[nodes_.size() - 1].getPosition().y)));
	// 	break;
	// }
}

void Snake::more_grow(){
	SnakeNode snode;
	snode.setAngle(nodes_[nodes_.size() - 1].getAngle());
	snode.setPosition(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x, 
								   nodes_[nodes_.size() - 1].getPosition().y));
	nodes_.push_back(snode);
}

// unsigned Snake::getSize() const
// {
// 	return nodes_.size();
// }

unsigned Snake::getSize() const
{
	return nodes_.size() + 1;
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{

	for (decltype(nodes_.size()) i = InitialSize; i < nodes_.size(); ++i)
	{
		if (snake_head.getBounds2().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true; 
		}
	}
}

void Snake::checkEdgeCollisions()
{

	if (snake_head.getHeadPosition().x <= 0)
		snake_head.setHeadPosition(sf::Vector2f(Game::Width, snake_head.getHeadPosition().y));
	else if (snake_head.getHeadPosition().x >= Game::Width)
		snake_head.setHeadPosition(sf::Vector2f(0, snake_head.getHeadPosition().y));
	else if (snake_head.getHeadPosition().y <= 0)
		snake_head.setHeadPosition(sf::Vector2f(snake_head.getHeadPosition().x, Game::Height));
	else if (snake_head.getHeadPosition().y >= Game::Height)
		snake_head.setHeadPosition(sf::Vector2f(snake_head.getHeadPosition().x, 0));
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setAngle(nodes_.at(i - 1).getAngle());
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}
	nodes_[0].setAngle(snake_head.getHeadAngle());
	nodes_[0].setPosition(snake_head.getHeadPosition());
	snake_head.move(my_direction.x, my_direction.y);
	// nodes_[0].move(my_direction.x, my_direction.y);

	// switch (direction_)
	// {
	// case Direction::Up:
	// 	nodes_[0].move(0, -SnakeNode::Height);
	// 	break;
	// case Direction::Down:
	// 	nodes_[0].move(0, SnakeNode::Height);
	// 	break;
	// case Direction::Left:
	// 	nodes_[0].move(-SnakeNode::Width, 0);
	// 	break;
	// case Direction::Right:
	// 	nodes_[0].move(SnakeNode::Width, 0);
	// 	break;
	// }
}

void Snake::render(sf::RenderWindow& window)
{
	
	for (int i = nodes_.size()-1; i>=0; --i){
		nodes_[i].render(window);
	}
	snake_head.render(window);
}

void Snake::knn(std::vector<Fruit>& fruits){
	float max_value = -1;
	sf::Vector2f knn_best = sf::Vector2f(0,0);
	if(flag.y == 1){
		for(auto& fruit : fruits){
			int value;
			sf::Vector2f temp = sf::Vector2f(fruit.getPosition().x - snake_head.getHeadPosition().x, fruit.getPosition().y - snake_head.getHeadPosition().y);
			float distance = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
			if (fruit.getColor() == sf::Color::Black || fruit.getColor() == sf::Color(139, 69, 19)) value = 0;
			else if (fruit.getColor() == sf::Color::Red)   value = 3;
			else if (fruit.getColor() == sf::Color::Blue)  value = 2;
			else if (fruit.getColor() == sf::Color::Green) value = 1;
			if(value/distance >= max_value && getAngleBetweenVectors(my_direction, temp) < 90 && flag.y == 1){
				// std::cout<<"开始查找"<<std::endl;
				max_value = value/distance;
				knn_best.x =  temp.x * Speed / distance;
				knn_best.y =  temp.y * Speed / distance;
			} 
		}
		if(knn_best != sf::Vector2f(0,0)){
			my_direction = knn_best;
			flag.y = -1;
		}
		// std::cout<<"flag.y置为-1"<<std::endl;
	}
}

float Snake::getAngleBetweenVectors(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    // 计算两个向量的点积
    float dotProduct = v1.x * v2.x + v1.y * v2.y;

    // 计算两个向量的模
    float v1Length = std::sqrt(v1.x * v1.x + v1.y * v1.y);
    float v2Length = std::sqrt(v2.x * v2.x + v2.y * v2.y);

    // 计算夹角的余弦值
    float cosAngle = dotProduct / (v1Length * v2Length);

    // 使用反余弦函数计算夹角（以弧度为单位）
    float angleRad = std::acos(cosAngle);

    // 将弧度转换为度数
    float angleDeg = angleRad * 180.0f / 3.14159265359f;

    return angleDeg;
}