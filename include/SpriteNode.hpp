#ifndef SKELETON_SPRITENODE_HPP
#define SKELETON_SPRITENODE_HPP
#include "DrawableNode.hpp"
#include "Resource.hpp"
#include "ResourceManager.hpp"
#include <string>
namespace skeleton {
class SpriteNode : public DrawableNode {
public:
  SpriteNode() : DrawableNode(){};
  SpriteNode(std::string source, double x, double y) : DrawableNode() {
    this->source = source;
    this->x = x;
    this->y = y;
    skeleton::ResourceManager::get_instance().load_texture(source, this->tag);
  };

  void handle_draw() override {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = 64;
    dest.h = 64;
    skeleton::Renderer::get_instance().draw_texture(this->tag, nullptr, &dest);
  }

  void handle_update(double dt) override {}

  void handle_fixed_update(double dt) override {}

private:
  std::string source;
};
#endif
} // namespace skeleton
