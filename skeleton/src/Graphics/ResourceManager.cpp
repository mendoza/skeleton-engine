#include "skeleton/Graphics/ResourceManager.hpp"
#include "skeleton/Graphics/resource.hpp"
#include <memory>

namespace skeleton {
ResourceManager::ResourceManager() {
  skeleton::Logger::get_instance()->info("Created resource manager");
};

ResourceManager::~ResourceManager() {
  skeleton::Logger::get_instance()->info("Deleting resource manager");
  skeleton::Logger::get_instance()->info("Unloading resources");
  for (auto &resource : resources) {
    skeleton::Logger::get_instance()->info("Deleting resource with tag: " +
                                           std::to_string(resource.first));
    resource.second.get()->unload();
  }
  skeleton::Logger::get_instance()->info("Resources unloaded");
}

std::shared_ptr<Resource> ResourceManager::load_texture(std::string path) {
  std::hash<std::string> hash_fn;
  size_t tag = hash_fn(path);
  auto it = resources.find(tag);
  if (it != resources.end()) {
    return it->second;
  }

  auto texture = std::make_shared<TextureResource>(path);
  if (texture.get()->load()) {
    texture->tag = tag;
    resources[tag] = texture;
    return texture;
  }
  return nullptr;
}

std::shared_ptr<Resource> ResourceManager::get(size_t resource_id) {
  auto it = resources.find(resource_id);
  if (it != resources.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}
} // namespace skeleton
