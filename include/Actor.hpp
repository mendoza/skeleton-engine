#pragma once
#include <Components.hpp>
class Actor : public ecs::EntityAlias<GraphicComponent> {
  public:
	Actor() {}
	Actor(skeleton::GameDataRef Data, sol::table GC);
	~Actor();
	void rotate(float Angle);
	void forward(float Speed);
	void backward(float Speed);
	void stop();
	void flipH();
	void flipV();
	void playAnimation(std::string Name);
	sf::Vector2f getPosition();

  private:
	sf::Vector2f getSpriteDirection(float rotation);
};