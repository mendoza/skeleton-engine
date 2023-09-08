#include "Actor.hpp"

Actor::Actor(const std::string& texture_name) {
	this->add<GraphicComponent>(texture_name);
	this->add<PositionComponent>(0, 0);
}

Actor::~Actor() = default;
