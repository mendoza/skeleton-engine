#include <memory>
#include <skeleton/core/Resource.hpp>
#include <skeleton/core/ResourceManager.hpp>
#include <skeleton/graphics/TextureResource.hpp>

namespace skeleton::core {
ResourceManager::ResourceManager() {
  skeleton::core::Logger::get_instance()->info("Created resource manager");
};

ResourceManager::~ResourceManager() {
  skeleton::core::Logger::get_instance()->info("Deleting resource manager");
  skeleton::core::Logger::get_instance()->info("Unloading resources");
  for (auto &resource : resources) {
    skeleton::core::Logger::get_instance()->info(
        "Deleting resource with tag: " + std::to_string(resource.first));
    resource.second.get()->unload();
  }
  skeleton::core::Logger::get_instance()->info("Resources unloaded");
}

std::shared_ptr<skeleton::graphics::TextureResource>
ResourceManager::load_texture(std::string path) {
  std::hash<std::string> hash_fn;
  size_t tag = hash_fn(path);
  auto it = resources.find(tag);
  if (it != resources.end()) {
    return std::dynamic_pointer_cast<skeleton::graphics::TextureResource>(
        it->second);
  }

  auto texture = std::make_shared<skeleton::graphics::TextureResource>(path);
  if (texture.get()->load()) {
    texture->tag = tag;
    resources[tag] = texture;
    return texture;
  }
  return nullptr;
}

std::shared_ptr<skeleton::graphics::TextureResource>
ResourceManager::get(size_t resource_id) {
  auto it = resources.find(resource_id);
  if (it != resources.end()) {
    return std::dynamic_pointer_cast<skeleton::graphics::TextureResource>(
        it->second);
  } else {
    return nullptr;
  }
}
} // namespace skeleton::core
