#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <Components.hpp>
#include <OpenECS.hpp>
#include <SFML/System/Vector2.hpp>
#include <sol.hpp>
#include <string>

class Actor : public ecs::EntityAlias<GraphicComponent> {
  public:
	Actor() {}
	Actor(skeleton::GameDataRef data, sol::table graphic_component);
	~Actor();
	void rotate(float angle);
	void move(sf::Vector2f direction);
	void stop();
	void flip_horizontal();
	void flip_vertical();
	void play_animation(std::string name, bool should_loop);
	sf::Vector2f get_position();
	sf::Vector2f get_direction();
};

#endif