#ifndef SKELETON_SYSTEMS_HPP
#define SKELETON_SYSTEMS_HPP

#include <Components.hpp>
#include <OpenECS.hpp>

class GraphicSystem : public ecs::System {
  public:
	GraphicSystem() {}
	void update(float time) override {
		for (auto entity : entities().with<GraphicComponent>()) {
			entity.get<GraphicComponent>().update_component(time);
		}
	}
};

#endif