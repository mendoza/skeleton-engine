#include "Actor.hpp"
Actor::Actor(skeleton::GameDataRef Data, std::string Path) {
	sol::state L;
	L.script_file(Path);
	L.open_libraries();

	this->add<GraphicComponent>(Data, L["graphicComponent"]);
	this->add<LogicComponent>(Path);
	this->get<LogicComponent>().L.set_function("rotate", &Actor::rotate, *this);
	this->get<LogicComponent>().L.set_function("forward", &Actor::forward,
											   *this);
	this->get<LogicComponent>().L.set_function("backward", &Actor::backward,
											   *this);
	this->get<LogicComponent>().L.set_function("stop", &Actor::stop, *this);
	this->get<LogicComponent>().L.set_function("playAnimation",
											   &Actor::playAnimation, *this);
}

Actor::~Actor() {}

void Actor::rotate(float Angle) {
	this->get<GraphicComponent>().Sprite.rotate(Angle);
	this->get<GraphicComponent>().SpriteRotation += Angle;
}

void Actor::forward(float Speed) {
	float angle = this->get<GraphicComponent>().SpriteRotation * (M_PI / 180.f);
	sf::Vector2f direction = {cos(-angle), sin(-angle)};
	direction *= Speed;
	this->get<GraphicComponent>().Sprite.move(direction);
}

void Actor::backward(float Speed) {
	float angle = this->get<GraphicComponent>().SpriteRotation * (M_PI / 180.f);
	sf::Vector2f direction = {cos(-angle), sin(-angle)};
	direction *= -Speed;
	this->get<GraphicComponent>().Sprite.move(direction);
}
void Actor::stop() {}

void Actor::playAnimation(std::string Name) {
	if (this->get<GraphicComponent>().Animated) {
		int row = this->get<GraphicComponent>().Animations.getAnimation(Name);
		this->get<GraphicComponent>().CurrentImage.y = row;
		this->get<GraphicComponent>().CurrentAnimation = Name;
	}
}