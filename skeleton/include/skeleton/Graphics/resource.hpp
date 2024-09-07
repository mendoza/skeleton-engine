#ifndef SKELETON_RESOURCE_HPP
#define SKELETON_RESOURCE_HPP
#include "skeleton/Core/Logger.hpp"
#include "skeleton/Graphics/Renderer.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <sol/sol.hpp>
#include <string>
namespace skeleton {
class Resource {
public:
  std::size_t last_accessed_at;
  bool is_loaded = false;
  size_t tag;
  Resource() {
    this->last_accessed_at = -1;
  }
  virtual ~Resource() {}
  virtual bool load() = 0;
  virtual void unload() = 0;
};

class TextureResource : public Resource {
public:
  TextureResource(std::string path) : Resource() {
    this->path = path;
  }

  ~TextureResource() override {
    unload();
  }

  bool load() override{
    texture = IMG_LoadTexture(skeleton::Renderer::get_instance().get_renderer(),
                              path.c_str());
    if (!texture) {
      skeleton::Logger::get_instance()->error("Failed to load texture: " +
                                              path);
      skeleton::Logger::get_instance()->error("SDL Error: " +
                                              std::string(SDL_GetError()));
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
} // namespace skeleton
#endif
