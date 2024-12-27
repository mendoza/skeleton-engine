#ifndef SKELETON_RESOURCE_HPP
#define SKELETON_RESOURCE_HPP
#include "skeleton/core/Logger.hpp"
#include "skeleton/graphics/Renderer.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <sol/sol.hpp>
#include <string>
namespace skeleton::core {
class Resource {
public:
  std::size_t last_accessed_at;
  bool is_loaded = false;
  size_t tag;
  Resource() { this->last_accessed_at = -1; }
  virtual ~Resource() {}
  virtual bool load() = 0;
  virtual void unload() = 0;
};

} // namespace skeleton::core
#endif
