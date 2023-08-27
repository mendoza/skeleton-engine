#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Components.hpp"
#include "OpenECS.hpp"
#include <sol/sol.hpp>
#include <string>

class Actor : public ecs::EntityAlias<GraphicComponent, PositionComponent> {
  public:
	Actor() {}
	Actor(std::string texture_name);
	~Actor();
};

#endif