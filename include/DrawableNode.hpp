#ifndef SKELETON_DRAWABLENODE_HPP
#define SKELETON_DRAWABLENODE_HPP
#include "Node2D.hpp"
#include <string>
namespace skeleton {
class DrawableNode : public Node2D {
public:
  DrawableNode() : Node2D(){
    this->name = "DrawableNode";
  };
  DrawableNode(std::string tag) : Node2D(tag){
    this->name = "DrawableNode";
  };

  virtual ~DrawableNode() {}
  virtual void draw() {
    handle_draw();
    for (auto child : this->children) {
      if (dynamic_cast<DrawableNode *>(child))
        dynamic_cast<DrawableNode *>(child)->draw();
    }
  }

  virtual void handle_draw() = 0;
};
} // namespace skeleton
#endif
