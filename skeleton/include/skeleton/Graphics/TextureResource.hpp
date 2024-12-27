#ifndef TEXTURERESOURCE_HPP
#define TEXTURERESOURCE_HPP
#include "skeleton/core/Logger.hpp"
#include "skeleton/core/Resource.hpp"
#include "skeleton/graphics/Renderer.hpp"
namespace skeleton::graphics {
class TextureResource : public skeleton::core::Resource {
public:
  TextureResource(std::string path) : Resource() { this->path = path; }

  ~TextureResource() override { unload(); }

  bool load() override {
    texture = IMG_LoadTexture(
        skeleton::graphics::Renderer::get_instance().get_renderer(),
        path.c_str());
    if (!texture) {
      skeleton::core::Logger::get_instance()->error("Failed to load texture: " +
                                                    path);
      skeleton::core::Logger::get_instance()->error(
          "SDL Error: " + std::string(SDL_GetError()));
      return false;
    }
    is_loaded = true;
    return true;
  }

  void unload() override {
    if (texture != nullptr) {
      SDL_DestroyTexture(texture);
      texture = nullptr;
      is_loaded = false;
    }
  }

  friend class Renderer;

private:
  SDL_Texture *texture = nullptr;
  std::string path;
};

} // namespace skeleton::graphics
#endif
