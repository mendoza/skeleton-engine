#include <Actor.hpp>

Actor::Actor(skeleton::GameDataRef data, sol::table graphic_component) {
	this->add<GraphicComponent>(data, graphic_component);
	this->add<PositionComponent>(0, 0);
}

Actor::~Actor() {}

void Actor::rotate(float angle) {
	this->get<GraphicComponent>().sprite.rotate(angle);
}

sf::Vector2f Actor::get_direction() {
	float rotation = this->get<GraphicComponent>().get_sprite_rotation();
	float angle = rotation * (M_PI / 180.f);
	return sf::Vector2f(cos(-angle), sin(-angle));
}

void Actor::move(sf::Vector2f direction) {
	this->get<GraphicComponent>().sprite.move(direction);
}

void Actor::stop() { this->get<GraphicComponent>().sprite.move({0.f, 0.f}); }

void Actor::flip_horizontal() {
	sf::Vector2f scale = this->get<GraphicComponent>().sprite.getScale();
	scale.x *= -1;

	this->get<GraphicComponent>().sprite.setScale(scale);
	sf::Vector2f direction = this->get_direction();
	this->get<GraphicComponent>().set_sprite_rotation(
		std::atan2(direction.y, -direction.x) * 180 / M_PI);
}

void Actor::flip_vertical() {
	sf::Vector2f scale = this->get<GraphicComponent>().sprite.getScale();
	scale.y *= -1;

	this->get<GraphicComponent>().sprite.setScale(scale);
	sf::Vector2f direction = this->get_direction();
	this->get<GraphicComponent>().set_sprite_rotation(
		std::atan2(-direction.y, direction.x) * 180 / M_PI);
}

void Actor::play_animation(std::string name) {
	if (this->get<GraphicComponent>().get_is_animated()) {
		this->get<GraphicComponent>().play_animation(name);
	}
}

sf::Vector2f Actor::get_position() {
	return this->get<GraphicComponent>().sprite.getPosition();
}