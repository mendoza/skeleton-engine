#ifndef SKELETON_RESOURCE_MANAGER_HPP
#define SKELETON_RESOURCE_MANAGER_HPP

#include "Resource.hpp"
#include "Service.hpp"
#include <SDL.h>
#include <map>
#include <string>

namespace skeleton {
class ResourceManager : public Service {
public:
  static ResourceManager& get_instance() {
    static ResourceManager instance;
    return instance;
  }

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  void add(Resource *resource);
  Resource *get(std::string name);

private:
  ResourceManager();
  ~ResourceManager();

  std::map<std::string, Resource *> resources;
};
} // namespace skeleton

#endif
