#ifndef SKELETON_RESOURCE_HPP
#define SKELETON_RESOURCE_HPP
#include <SDL2/SDL.h> // Updated include statement
#include <sol/sol.hpp>
#include <string>
namespace skeleton {
class Resource {
public:
  std::string name;
  std::size_t last_accessed_at;
  Resource(std::string name) : name(name) { this->last_accessed_at = 0; }
  virtual ~Resource() {}
  virtual void unload() = 0;
};

class TextureResource : public Resource {
public:
  TextureResource(std::string name) : Resource(name) {}
  void unload() override {
    if (texture) {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
  }

private:
  SDL_Texture *texture;
};
} // namespace skeleton
#endif
