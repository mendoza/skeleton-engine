
#ifndef SKELETON_NODE2D_HPP
#define SKELETON_NODE2D_HPP
#include "Node.hpp"
#include <string>
namespace skeleton {
class Node2D : public Node {
protected:
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
  int rotation = 0;
  int scale_x = 1;
  int scale_y = 1;

public:
  Node2D() : Node(){};
  Node2D(std::string tag) : Node(tag){};

  virtual void update(double deltaTime) {
    handle_update(deltaTime);
    for (auto child : this->children) {
      if (dynamic_cast<Node2D *>(child))
        dynamic_cast<Node2D *>(child)->update(deltaTime);
    }
  }

  virtual void fixed_update(double deltaTime) {
    handle_fixed_update(deltaTime);
    for (auto child : this->children) {
      if (dynamic_cast<Node2D *>(child))
        dynamic_cast<Node2D *>(child)->fixed_update(deltaTime);
    }
  }

  virtual void handle_update(double deltaTime) = 0;
  virtual void handle_fixed_update(double deltaTime) = 0;
};
} // namespace skeleton
#endif
