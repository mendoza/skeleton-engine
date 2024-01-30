#ifndef SKELETON_NODE_HPP
#define SKELETON_NODE_HPP
#include "ServiceLocator.hpp"
#include "SkeletonRenderer.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
namespace skeleton {
class Node {
public:
  std::string tag;
  virtual void update(double deltaTime) {
    for (auto child : children) {
      child->update(deltaTime);
    }
  }

  virtual void draw() {
    for (auto child : children) {
      child->draw();
    }
  }

  virtual void handle_input(SDL_Event &event) {
    for (auto child : children) {
      child->handle_input(event);
    }
  }

  void addChild(Node *child) { children.push_back(child); }

  std::vector<Node *> children;

protected:
};
} // namespace skeleton
#endif
