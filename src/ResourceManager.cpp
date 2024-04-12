#include "ResourceManager.hpp"

namespace skeleton {
ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() {
  for (auto &resource : resources) {
    resource.second->unload();
    delete resource.second;
  }
}


bool ResourceManager::load_texture(std::string path, std::string tag) {
  TextureResource *texture = new TextureResource(path, tag);
  if (texture->load()) {
    resources[tag] = texture;
    return true;
  }
  delete texture;
  return false;
}

std::string ResourceManager::load_texture(std::string path) {
  TextureResource *texture = new TextureResource(path);
  if (texture->load()) {
    resources[texture->tag] = texture;
    return texture->tag;
  }
  return "";
}


Resource *ResourceManager::get(std::string name) {
  if (resources.find(name) != resources.end()) {
    resources[name]->last_accessed_at = SDL_GetTicks64();
    return resources[name];
  }
  return nullptr;
}
} // namespace skeletor