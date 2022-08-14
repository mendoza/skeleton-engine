#include "Actor.hpp"
Actor::Actor(skeleton::GameDataRef Data, sol::table GC) {
	this->add<GraphicComponent>(Data, GC);
}

Actor::~Actor() {}

void Actor::rotate(float Angle) {
	this->get<GraphicComponent>().Sprite.rotate(Angle);
}

sf::Vector2f Actor::getDirection() {
	float rotation = this->get<GraphicComponent>().getSpriteRotation();
	float angle = rotation * (M_PI / 180.f);
	return sf::Vector2f(cos(-angle), sin(-angle));
}

void Actor::move(sf::Vector2f direction) {
	this->get<GraphicComponent>().Sprite.move(direction);
}

void Actor::stop() { this->get<GraphicComponent>().Sprite.move({0.f, 0.f}); }

void Actor::flip_horizontal() {
	sf::Vector2f scale = this->get<GraphicComponent>().Sprite.getScale();
	scale.x *= -1;

	this->get<GraphicComponent>().Sprite.setScale(scale);
	sf::Vector2f direction = this->getDirection();
	this->get<GraphicComponent>().setSpriteRotation(
		std::atan2(direction.y, -direction.x) * 180 / M_PI);
}

void Actor::flip_vertical() {
	sf::Vector2f scale = this->get<GraphicComponent>().Sprite.getScale();
	scale.y *= -1;

	this->get<GraphicComponent>().Sprite.setScale(scale);
	sf::Vector2f direction = this->getDirection();
	this->get<GraphicComponent>().setSpriteRotation(
		std::atan2(-direction.y, direction.x) * 180 / M_PI);
}

void Actor::playAnimation(std::string Name, bool shouldLoop = false) {
	if (this->get<GraphicComponent>().getIsAnimated()) {
		this->get<GraphicComponent>().playAnimation(Name, shouldLoop);
	}
}

sf::Vector2f Actor::getPosition() {
	return this->get<GraphicComponent>().Sprite.getPosition();
}