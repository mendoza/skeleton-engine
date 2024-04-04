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
  virtual void unload() = 0;
};

class TextureResource : public Resource {
public:
  TextureResource(std::string path) : Resource() {
    std::cout << "Texture resource created" << std::endl;
    this->path = path;
    std::cout << path << std::endl;
    this->tag = skeleton::guid::generate();
    this->texture = IMG_LoadTexture(
        skeleton::Renderer::get_instance().get_renderer(), path.c_str());
    // check for error
    if (!texture) {
      skeleton::Logger::get_instance()->error("Failed to load texture: " +
                                              path);
      skeleton::Logger::get_instance()->error("SDL Error: " +
                                              std::string(SDL_GetError()));
    } else {
      skeleton::Logger::get_instance()->info("Texture loaded successfully");
    }
  }

  void unload() override {
    if (texture) {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
  }

  SDL_Texture *texture;

private:
  std::string path;
};
} // namespace skeleton
#endif
