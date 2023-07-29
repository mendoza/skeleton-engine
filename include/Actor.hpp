#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <Components.hpp>
#include <OpenECS.hpp>
#include <sol.hpp>
#include <string>

class Actor : public ecs::EntityAlias<GraphicComponent, PositionComponent> {
  public:
	Actor() {}
	Actor(skeleton::GameDataRef data, sol::table graphic_component);
	~Actor();
	void flip_horizontal();
	void flip_vertical();
	void play_animation(std::string name);
};

#endif