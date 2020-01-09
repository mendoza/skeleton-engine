#pragma once
#include <Components.hpp>
#include <ECS.hpp>
#include <Game.hpp>

namespace Skeleton {
class drawGraphicSystem : public System {
public:
  gameDataRef data;
  drawGraphicSystem(gameDataRef data) { this->data = data; }
  void update(float time) override {
    // Get the entity manager using entities() function
    for (auto entity : entities().with<GraphicComponent>()) {
      entity.get<GraphicComponent>().update(time);
      this->data->window.draw(entity.get<GraphicComponent>().sprite);
    }
  }
};

class movingGraphicSystem : public System {
public:
  gameDataRef data;
  movingGraphicSystem(gameDataRef data) { this->data = data; }
  void update(float time) override {
    // Get the entity manager using entities() function
    for (auto entity : entities().with<GraphicComponent, movableComponent>()) {
      entity.get<GraphicComponent>().sprite.setPosition(10, 10);
    }
  }
};
} // namespace Skeleton