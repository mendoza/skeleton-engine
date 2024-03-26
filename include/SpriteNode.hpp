#ifndef SKELETON_SPRITENODE_HPP
#define SKELETON_SPRITENODE_HPP
#include <string>
#include "DrawableNode.hpp"
namespace skeleton {
class SpriteNode : public DrawableNode {
public:
  std::string source; 
  SpriteNode() : DrawableNode(){};
  SpriteNode(std::string source, std::string tag) : DrawableNode(tag){
        this->source = source; 
  };

  virtual void update(double delta) override {

  }

  virtual void draw() override {
     
  }
};
#endif
} // namespace skeleton
