#pragma once
#include <string>
#include <unordered_map>

namespace skeleton::core {

class ResourceManager {
public:
  static ResourceManager &get_instance() {
    static ResourceManager instance;
    return instance;
  }
  ResourceManager(const ResourceManager &)            = delete;
  ResourceManager &operator=(const ResourceManager &) = delete;

  // Loads a texture from disk and stores it in the Renderer.
  // Safe to call multiple times with the same path — returns the cached key.
  size_t load_texture(const std::string &path);

private:
  ResourceManager() = default;

  std::unordered_map<std::string, size_t> cache_;
};

} // namespace skeleton::core
