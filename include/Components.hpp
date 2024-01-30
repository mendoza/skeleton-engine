#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP
#include "Node.hpp"
#include "ServiceLocator.hpp"
#include "SkeletonRenderer.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
namespace skeleton {
class TransformNode : public Node {
public:
  float x;
  float y;
  float rotation;
  float scale_x;
  float scale_y;
};

class DrawableNode : public TransformNode {
public:
  virtual void draw() = 0;
};

class Particle : public DrawableNode {
public:
  int width = 10;
  int r, g, b = 0;
  int velocity_x = 0;
  int velocity_y = 0;
  Particle(std::string tag, int x, int y) {
    this->tag = tag;
    this->x = x;
    this->y = y;
    this->rotation = 0;
    this->scale_x = 1;
    this->scale_y = 1;
    this->r = rand() % 255;
    this->g = rand() % 255;
    this->b = rand() % 255;
    // define velocity to scatter squares
  };

  virtual void draw() override {
    skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->draw_rect(
        this->x, this->y, this->width, this->width, this->r, this->g, this->b,
        255);
  };

  virtual void update(double deltaTime) override {
    this->x += velocity_x * deltaTime;
    this->y += velocity_y * deltaTime;
  };
};

class ParticleSystem : public DrawableNode {
public:
  ParticleSystem(std::string tag, int x, int y) {
    this->tag = tag;
    this->x = x;
    this->y = y;
    this->rotation = 0;
    this->scale_x = 1;
    this->scale_y = 1;
    for (int i = 0; i < 100; i++) {
      this->children.push_back(
          new Particle("particle_id: " + std::to_string(i), this->x, this->y));
    }
  };

  virtual void draw() override {
    for (auto &particle : this->children) {
      particle->draw();
    }
  };

  virtual void update(double deltaTime) override {
    // keep adding particles to look like a flow of particles
    if (this->children.size() < 100) {
      this->children.push_back(
          new Particle("particle_id: " + std::to_string(this->children.size()),
                       this->x, this->y));
    }
    for (auto &node : this->children) {
      auto particle = dynamic_cast<Particle *>(node);
      particle->velocity_y += 1;
      if (particle->y > 600) {
        this->children.erase(
            std::remove(this->children.begin(), this->children.end(), node),
            this->children.end());
      } else {
        particle->update(deltaTime);
      }
    }
  };
};

} // namespace skeleton
#endif
