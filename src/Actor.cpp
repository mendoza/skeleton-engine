#include <Actor.hpp>

Actor::Actor(skeleton::GameDataRef data, sol::table graphic_component) {
	this->add<GraphicComponent>(data, graphic_component);
	this->add<PositionComponent>(0, 0);
}

Actor::~Actor() {}

void Actor::flip_horizontal() {}

void Actor::flip_vertical() {}

void Actor::play_animation(std::string name) {
	if (this->get<GraphicComponent>().get_is_animated()) {
		this->get<GraphicComponent>().play_animation(name);
	}
}
