#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP
#include "DrawableNode.hpp"
#include "ServiceLocator.hpp"
#include "SkeletonRenderer.hpp"
#include <SDL.h>

namespace skeleton {
class Particle : public DrawableNode {
public:
  int life_time = 0;
  int r, g, b = 0;
  int velocity_x = 0;
  int velocity_y = 0;
  Particle(std::string tag, int x, int y, int velocity_x = 0,
           int velocity_y = 0): DrawableNode(tag) {
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
    skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->draw_rect(
        this->x, this->y, this->width * this->scale_x,
        this->width * this->scale_y, this->r, this->g, this->b, 255);
  };

  virtual void handle_update(double deltaTime) override {
    // std::cout << "Particle update"/*  */ << deltaTime << std::endl;
    this->life_time++;
    this->x += velocity_x * deltaTime;
    this->y += velocity_y * deltaTime;
  };
};

class ParticleSystem : public DrawableNode {
  int last_spawn = 0;

public:
  ParticleSystem(std::string tag, int x, int y): DrawableNode(tag) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < 360; i++) {
      // create a particle with 2d velocity to form a circle
      // with radius 1000
      int velocity_x = cos(i) * 1000;
      int velocity_y = sin(i) * 1000;
      this->addChild(new Particle("particle", x, y, velocity_x, velocity_y));
      this->last_spawn++;
    }
  };

  virtual void handle_draw() override {
  };

  virtual void handle_update(double dt) override {
  }
};
} // namespace skeleton
#endif
