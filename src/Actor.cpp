#include "Actor.hpp"
Actor::Actor(Skeleton::GameDataRef Data, std::string Path) {
	sol::state L;
	L.script_file(Path);

	this->add<GraphicComponent>(Data, L["graphicComponent"]);
	this->add<LogicComponent>(Path);
	this->get<LogicComponent>().L.set_function("rotate", &Actor::rotate, *this);
	this->get<LogicComponent>().L.set_function("forward", &Actor::forward,
											   *this);
	this->get<LogicComponent>().L.set_function("backward", &Actor::backward,
											   *this);
	this->get<LogicComponent>().L.set_function("stop", &Actor::stop, *this);
}

Actor::~Actor() {}

void Actor::rotate(float Angle) {
	this->get<GraphicComponent>().Sprite.rotate(Angle);
	this->get<GraphicComponent>().SpriteRotation += Angle;
}

void Actor::forward() {
	float speed = this->get<LogicComponent>().L["physics"]["speed"];
	float angle = this->get<GraphicComponent>().SpriteRotation * (M_PI / 180.f);
	sf::Vector2f direction = {cos(-angle), sin(-angle)};
	direction *= speed;
	this->get<GraphicComponent>().Sprite.move(direction);
}

void Actor::backward() {
	float speed = this->get<LogicComponent>().L["physics"]["speed"];
	float angle = this->get<GraphicComponent>().SpriteRotation * (M_PI / 180.f);
	sf::Vector2f direction = {cos(-angle), sin(-angle)};
	direction *= -speed;
	this->get<GraphicComponent>().Sprite.move(direction);
}
void Actor::stop() {}