#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <Components.hpp>
#include <OpenECS.hpp>
#include <sol/sol.hpp>
#include <string>

class Actor : public ecs::EntityAlias<GraphicComponent, PositionComponent> {
  public:
	Actor() {}
	Actor(sol::table graphic_component);
	~Actor();
};

#endif