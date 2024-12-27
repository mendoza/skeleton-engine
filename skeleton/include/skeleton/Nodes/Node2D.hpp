#ifndef SKELETON_NODE2D_HPP
#define SKELETON_NODE2D_HPP
#include "Node.hpp"
#include <string>
namespace skeleton::nodes {
class Node2D : public skeleton::nodes::Node {
public:
  double x = 0;
  double y = 0;
  int width = 0;
  int height = 0;
  int rotation = 0;
  int scale_x = 1;
  int scale_y = 1;

  Node2D() : Node() { this->name = "Node2D"; };
  Node2D(std::string uid) : Node(uid) { this->name = "Node2D"; };
  virtual ~Node2D() {}

  virtual void update(double dt) {
    handle_update(dt);
    for (auto child : this->children) {
      if (auto node2D = dynamic_cast<Node2D *>(child))
        node2D->update(dt);
    }
  }

  virtual void fixed_update(double dt) {
    handle_fixed_update(dt);
    for (auto child : this->children) {
      if (dynamic_cast<Node2D *>(child))
        dynamic_cast<Node2D *>(child)->fixed_update(dt);
    }
  }

  virtual void handle_update(double dt) = 0;
  virtual void handle_fixed_update(double dt) = 0;
};
} // namespace skeleton::nodes
#endif
