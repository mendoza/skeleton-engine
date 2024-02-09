#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP
#include "Node.hpp"
#include "ServiceLocator.hpp"
#include "SkeletonRenderer.hpp"
#include <SDL2/SDL.h>

namespace skeleton {
class Base2DNode : public Node<Base2DNode> {
public:
  Base2DNode() : Node("base_2d_node"){};
  virtual void update(double deltaTime) = 0;
};

class DrawableNode : public Base2DNode {
public:
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
  int rotation = 0;
  int scale_x = 1;
  int scale_y = 1;
  virtual void draw() = 0;

  virtual void update(double deltaTime) override {
    for (auto child : this->children) {
      child->update(deltaTime);
    }
  };
};

class Particle : public DrawableNode {
public:
  int width = 10;
  int life_time = 0;
  int r, g, b = 0;
  int velocity_x = 0;
  int velocity_y = 0;
  Particle(std::string tag, int x, int y, int velocity_x = 0,
           int velocity_y = 0) {
    this->tag = tag;
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

  virtual void draw() override {
    skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->draw_rect(
        this->x, this->y, this->width * this->scale_x,
        this->width * this->scale_y, this->r, this->g, this->b, 255);
  };

  virtual void update(double deltaTime) override {
    this->life_time++;
    this->x += velocity_x * deltaTime;
    this->y += velocity_y * deltaTime;
  };
};

class ParticleSystem : public DrawableNode {
  int last_spawn = 0;

public:
  ParticleSystem(std::string tag, int x, int y) {
    this->tag = tag;
    this->x = x;
    this->y = y;
    this->rotation = 0;
    this->scale_x = 1;
    this->scale_y = 1;
    for (int i = 0; i < 360; i++) {
      float angle = 2 * 3.14159 * float(i) / 360.0f;
      float velocity_x = cos(angle) * 10;
      float velocity_y = sin(angle) * 10;

      this->children.push_back(new Particle("particle_id: " + std::to_string(i),
                                            this->x, this->y, velocity_x,
                                            velocity_y));
      this->last_spawn++;
    }
  };

  virtual void draw() override {
    for (auto &particle : this->children) {
      // test if node is a particle by casting
      // if it is a particle, draw
      if (dynamic_cast<Particle *>(particle)) {
        dynamic_cast<Particle *>(particle)->draw();
      };
    }
  };

  virtual void update(double deltaTime) override {
    // keep adding particles to look like a flow of particles
    for (int i = 0; i < this->children.size(); i++) {
      auto particle = dynamic_cast<Particle *>(this->children[i]);
      if (particle->life_time > 10000) {
        this->children.erase(this->children.begin() + i);
        i--; // Decrement i to account for the erased element
      } else {
        particle->update(deltaTime);
      }
    }
  }
};
} // namespace skeleton
#endif
