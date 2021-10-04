#pragma once
#include <Components.hpp>
#include <Engine.hpp>

class GraphicSystem : public ecs::System {
  public:
	GraphicSystem() {}
	void update(float time) override {
		for (auto entity : entities().with<GraphicComponent>()) {
			entity.get<GraphicComponent>().update(time);
		}
	}
};

class LogicSystem : public ecs::System {
  public:
	LogicSystem() {}
	void update(float time) override {
		for (auto entity : entities().with<LogicComponent>()) {
			entity.get<LogicComponent>().update(time);
		}
	}
};
