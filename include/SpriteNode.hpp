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
    this->texture = new skeleton::TextureResource(source);
    skeleton::ResourceManager::get_instance().add(texture);
  };

  void handle_draw() override {
    if (texture) {
      SDL_Rect dest;
      dest.x = x;
      dest.y = y;
      dest.w = 64;
      dest.h = 64;
      // TODO: make it render resource instead of texture or resource tag
      skeleton::Renderer::get_instance().draw_texture(texture->texture, nullptr,
                                                      &dest);
    }
  }

  void handle_update(double dt) override {}

  void handle_fixed_update(double dt) override {}

private:
  std::string source;
  TextureResource *texture;
};
#endif
} // namespace skeleton
