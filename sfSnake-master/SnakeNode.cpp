#include <SFML/Graphics.hpp>
#include <cmath>
#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Radius = 30.f;
inline float Coll = 0.5*SnakeNode::Radius;
const float SnakeNode::Width  = 2*SnakeNode::Radius;
const float SnakeNode::Height = 0.6*SnakeNode::Radius;


SnakeNode::SnakeNode(sf::Vector2f position)
: position_(position)
{	
	setAngle(0);
	// deco_.setPosition(position_);
	shape_.setFillColor(sf::Color(252,86,86));
	deco_.setFillColor(sf::Color::Black);
	deco_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));
	shape_.setRadius(SnakeNode::Radius); // Set the radius of the circle
	shape_.setOrigin(sf::Vector2f(SnakeNode::Radius, SnakeNode::Radius)); // Set the origin to the center of the circle
	shape_.setPosition(position_);
	deco_.setPosition(cal_angle(position_, angle_));
	coll.setRadius(Coll); 
	coll.setOrigin(sf::Vector2f(Coll, Coll)); 
	coll.setPosition(position_);
	// shape_.setOutlineColor(sf::Color::White);
	// shape_.setOutlineThickness(-1.f);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
	deco_.setPosition(cal_angle(position_, angle_));
	coll.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
	deco_.setPosition(cal_angle(position_, angle_));
	coll.setPosition(position_);
}

// void SnakeNode::move(float xOffset, float yOffset)
// {
// 	position_.x += xOffset;
// 	position_.y += yOffset;
// 	shape_.setPosition(position_);
// 	deco_.setPosition(sf::Vector2f(position_.x - SnakeNode::Width/2, position_.y - SnakeNode::Height/2));
// }

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;

	float angle = std::atan2(yOffset, xOffset) * 180 / 3.1415926 + 90;
	setAngle(angle);

	shape_.setPosition(position_);
    deco_.setPosition(cal_angle(position_, angle));
	coll.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return coll.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
	window.draw(deco_);
}

void SnakeNode::setAngle(float angle){
	angle_ = angle;
	deco_.setRotation(angle);
}

float SnakeNode::getAngle(){
	return angle_;
}

SnakeHead::SnakeHead(sf::Vector2f position, sf::Texture* texture){
	head_angle = 0;
	head_position = position;
	sprite_.setScale(0.4f, 0.4f);
    sprite_.setPosition(position.x, position.y);
	head_coll.setRadius(Coll); 
	head_coll.setOrigin(sf::Vector2f(Coll, Coll)); 
	head_coll.setPosition(position);
    if (texture) {
        sprite_.setTexture(*texture);
        sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    }
}

void SnakeHead::setTexture(sf::Texture* texture) {
    if (texture) {
        sprite_.setTexture(*texture);
        sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    }
}

void SnakeHead::render(sf::RenderWindow& window) {
    window.draw(sprite_);
}

void SnakeHead::move(float xOffset, float yOffset){
	head_position.x += xOffset;
	head_position.y += yOffset;
	sprite_.setPosition(head_position.x, head_position.y);
	head_angle = std::atan2(yOffset, xOffset) * 180 / 3.1415926 + 90;
	sprite_.setRotation(head_angle);
	head_coll.setPosition(head_position);
}

sf::Vector2f SnakeHead::getHeadPosition(){
	return head_position;
}

float SnakeHead::getHeadAngle(){
	return head_angle;
}

void SnakeHead::setHeadPosition(sf::Vector2f position){
	head_position = position;
}
void SnakeHead::setHeadAngle(float angle){
	head_angle = angle;
}

sf::FloatRect SnakeHead::getBounds1() const{
	return sprite_.getGlobalBounds();
}

sf::FloatRect SnakeHead::getBounds2() const{
	return head_coll.getGlobalBounds();
}

int x = 1.2;
sf::Vector2f SnakeNode::cal_angle(sf::Vector2f position, float angle){
	return sf::Vector2f(position.x - x*(SnakeNode::Radius) * std::cos(angle * 3.1415926 / 180.0f),
                        position.y - x*(SnakeNode::Radius) * std::sin(angle * 3.1415926 / 180.0f));
}