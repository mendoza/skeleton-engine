#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP
#include "DrawableNode.hpp"
#include "Renderer.hpp"
#include <SDL.h>

namespace skeleton {
class Particle : public DrawableNode {
public:
  double life_time = 0;
  int r, g, b = 0;
  int velocity_x = 0;
  int velocity_y = 0;
  bool is_ready_to_die = false;
  Particle(int x, int y, int velocity_x = 0, int velocity_y = 0)
      : DrawableNode() {
    this->width = 10;
    this->x = x;
    this->y = y;
    this->rotation = 0;
    this->scale_x = 1;
    this->scale_y = 1;
    this->r = rand() % 255;
    this->g = rand() % 255;
    this->b = rand() % 255;
    this->velocity_x = velocity_x;
    this->velocity_y = velocity_y;
  };

  virtual void handle_draw() override {
    skeleton::Renderer::get_instance().draw_rect(
        this->x, this->y, this->width * this->scale_x,
        this->width * this->scale_y, this->r, this->g, this->b, 255);
  };

  virtual void handle_fixed_update(double deltaTime) override {
    this->life_time += deltaTime;
  };

  virtual void handle_update(double deltaTime) override {
    this->is_ready_to_die = this->life_time > 2;
    this->x += velocity_x * deltaTime;
    this->y += velocity_y * deltaTime;
  };
};

class ParticleSystem : public DrawableNode {
  int last_spawn = 0;

public:
  ParticleSystem(std::string tag, int x, int y) : DrawableNode(tag) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < 360; i++) {
      int velocity_x = cos(i) * 1000;
      int velocity_y = sin(i) * 1000;
      this->add_child(new Particle(x, y, velocity_x, velocity_y));
    }
  };

  virtual void handle_draw() override{};

  virtual void handle_fixed_update(double deltaTime) override {
    this->last_spawn += deltaTime;
  };

  virtual void handle_update(double dt) override {
    for (auto child : this->children) {
      if (dynamic_cast<Particle *>(child)) {
        Particle *particle = dynamic_cast<Particle *>(child);
        if (particle->is_ready_to_die) {
          skeleton::Logger::get_instance()->info("Particle is ready to die");
          // this->remove_child(particle->get_tag());
        }
      }
    }
  }
};
} // namespace skeleton
#endif
