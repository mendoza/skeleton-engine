#ifndef SKELETON_RESOURCE_MANAGER_HPP
#define SKELETON_RESOURCE_MANAGER_HPP

#include "skeleton/core/Resource.hpp"
#include "skeleton/core/Service.hpp"
#include "skeleton/graphics/TextureResource.hpp"
#include <SDL.h>
#include <map>
#include <string>

namespace skeleton::core {
class ResourceManager : public Service {
public:
  static ResourceManager &get_instance() {
    static ResourceManager instance;
    return instance;
  }

  ResourceManager(const ResourceManager &) = delete;
  ResourceManager &operator=(const ResourceManager &) = delete;

  std::shared_ptr<skeleton::graphics::TextureResource>
  load_texture(std::string path);
  std::shared_ptr<skeleton::graphics::TextureResource> get(size_t resource_id);

private:
  ResourceManager();
  ~ResourceManager();
  std::map<size_t, std::shared_ptr<skeleton::core::Resource>> resources;
};
} // namespace skeleton::core

#endif
