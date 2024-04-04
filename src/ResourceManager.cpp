#include "ResourceManager.hpp"

namespace skeleton {
ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() {
  for (auto &resource : resources) {
    resource.second->unload();
    delete resource.second;
  }
}

void ResourceManager::add(Resource *resource) {
  resources[resource->tag] = resource;
}

Resource *ResourceManager::get(std::string name) {
  if (resources.find(name) != resources.end()) {
    resources[name]->last_accessed_at = SDL_GetTicks64();
    return resources[name];
  }
  return nullptr;
}
} // namespace skeleton