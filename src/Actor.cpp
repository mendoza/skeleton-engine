#include "Actor.hpp"
Actor::Actor(skeleton::GameDataRef Data, sol::table GC) {
	this->add<GraphicComponent>(Data, GC);
}

Actor::~Actor() {}

void Actor::rotate(float Angle) {
	this->get<GraphicComponent>().Sprite.rotate(Angle);
}

sf::Vector2f Actor::getSpriteDirection(float rotation) {
	float angle = rotation * (M_PI / 180.f);
	return sf::Vector2f(cos(-angle), sin(-angle));
}

void Actor::forward(float Speed) {
	sf::Vector2f direction =
		this->getSpriteDirection(this->get<GraphicComponent>().SpriteRotation);
	direction *= Speed;
	this->get<GraphicComponent>().Sprite.move(direction);
}

void Actor::backward(float Speed) {
	sf::Vector2f direction =
		this->getSpriteDirection(this->get<GraphicComponent>().SpriteRotation);
	direction *= -Speed;
	this->get<GraphicComponent>().Sprite.move(direction);
}

void Actor::stop() {
	sf::Vector2f direction =
		this->getSpriteDirection(this->get<GraphicComponent>().SpriteRotation);
	direction *= 0.f;
	this->get<GraphicComponent>().Sprite.move(direction);
}

void Actor::flipH() {
	sf::Vector2f scale = this->get<GraphicComponent>().Sprite.getScale();
	scale.x *= -1;

	this->get<GraphicComponent>().Sprite.setScale(scale);
	sf::Vector2f direction =
		this->getSpriteDirection(this->get<GraphicComponent>().SpriteRotation);

	this->get<GraphicComponent>().SpriteRotation =
		std::atan2(direction.y, direction.x) * 180 / M_PI;
}

void Actor::flipV() {
	sf::Vector2f scale = this->get<GraphicComponent>().Sprite.getScale();
	scale.y *= -1;

	this->get<GraphicComponent>().Sprite.setScale(scale);
	sf::Vector2f direction =
		this->getSpriteDirection(this->get<GraphicComponent>().SpriteRotation);

	this->get<GraphicComponent>().SpriteRotation =
		std::atan2(direction.y, direction.x) * 180 / M_PI;
}

void Actor::playAnimation(std::string Name) {
	if (this->get<GraphicComponent>().Animated) {
		int row = this->get<GraphicComponent>().Animations.getAnimation(Name);
		this->get<GraphicComponent>().CurrentImage.y = row;
		this->get<GraphicComponent>().CurrentAnimation = Name;
	}
}

sf::Vector2f Actor::getPosition() {
	return this->get<GraphicComponent>().Sprite.getPosition();
}