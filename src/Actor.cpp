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
}

void Actor::forward() {
	float speed = this->get<LogicComponent>().L["physics"]["speed"];
}

void Actor::backward() {
	float speed = this->get<LogicComponent>().L["physics"]["speed"];
}
void Actor::stop() {}