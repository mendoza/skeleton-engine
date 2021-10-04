#pragma once
#include <Components.hpp>
class Actor : public ecs::EntityAlias<GraphicComponent, LogicComponent> {
  public:
	Actor() {}
	Actor(Skeleton::GameDataRef Data, std::string Path);
	~Actor();
	void rotate(float Angle);
	void forward();
	void backward();
	void stop();
};