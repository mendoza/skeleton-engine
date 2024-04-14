#ifndef SKELETON_RESOURCE_MANAGER_HPP
#define SKELETON_RESOURCE_MANAGER_HPP

#include "Resource.hpp"
#include "Service.hpp"
#include <SDL.h>
#include <map>
#include <memory>
#include <string>

namespace skeleton {
class ResourceManager : public Service {
public:
  static ResourceManager &get_instance() {
    static ResourceManager instance;
    return instance;
  }

  ResourceManager(const ResourceManager &) = delete;
  ResourceManager &operator=(const ResourceManager &) = delete;

  std::shared_ptr<Resource> load_texture(std::string path);
  std::shared_ptr<Resource> get(size_t resource_id);

private:
  ResourceManager();
  ~ResourceManager();
  std::map<size_t, std::shared_ptr<Resource>> resources;
};
} // namespace skeleton

#endif
