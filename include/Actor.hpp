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
	Actor(skeleton::GameDataRef Data, sol::table GC);
	~Actor();
	void rotate(float Angle);
	void move(sf::Vector2f direction);
	void stop();
	void flip_horizontal();
	void flip_vertical();
	void playAnimation(std::string Name, bool shouldLopp);
	sf::Vector2f getPosition();
	sf::Vector2f getDirection();
};

#endif