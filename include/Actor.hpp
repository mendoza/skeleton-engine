#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Components.hpp"
#include <sol/sol.hpp>
#include <string>

class Actor {
  public:
	Actor() = default;
	explicit Actor(const std::string& texture_name);
	~Actor();
};

#endif