#ifndef SKELETON_RESOURCE_HPP
#define SKELETON_RESOURCE_HPP
#include "Logger.hpp"
#include "Renderer.hpp"
#include "guid.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <sol/sol.hpp>
#include <string>
namespace skeleton {
class Resource {
public:
  std::string tag;
  std::size_t last_accessed_at;
  Resource() {
    this->tag = skeleton::guid::generate();
    this->last_accessed_at = 0;
  }
  Resource(std::string tag) : tag(tag) { this->last_accessed_at = 0; }
  virtual ~Resource() {}
  virtual bool load() = 0;
  virtual void unload() = 0;
};

class TextureResource : public Resource {
public:
  TextureResource(std::string path) : Resource() {
    this->path = path;
    this->tag = skeleton::guid::generate();
  }

  TextureResource(std::string path, std::string tag) : Resource(tag) {
    this->path = path;
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
    return true;
  }

  void unload() override {
    if (texture) {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
  }

  friend class Renderer;
private:
  SDL_Texture *texture;
  std::string path;
};
} // namespace skeleton
#endif
