#ifndef SKELETON_DRAWABLENODE_HPP
#define SKELETON_DRAWABLENODE_HPP
#include "Node2D.hpp"
#include <string>
namespace skeleton {
class DrawableNode : public Node2D {
public:
  DrawableNode() : Node2D(){};
  DrawableNode(std::string tag) : Node2D(tag){};
  virtual void draw() = 0;
};
#endif
} // namespace skeleton