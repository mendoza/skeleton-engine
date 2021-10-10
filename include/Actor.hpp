#pragma once
#include <Components.hpp>
class Actor : public ecs::EntityAlias<GraphicComponent, LogicComponent> {
  public:
	Actor() {}
	Actor(skeleton::GameDataRef Data, std::string Path);
	~Actor();
	void rotate(float Angle);
	void forward();
	void backward();
	void stop();
	void playAnimation(std::string Name);
};