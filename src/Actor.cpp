#include "Actor.hpp"

Actor::Actor(sol::table graphic_component) {
	this->add<GraphicComponent>(graphic_component);
	this->add<PositionComponent>(0, 0);
}

Actor::~Actor() {}
