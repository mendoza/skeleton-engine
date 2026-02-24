#pragma once
#include <string>
#include <unordered_map>

namespace skeleton::core {

class TextureManager {
public:
  static TextureManager &get_instance() {
    static TextureManager instance;
    return instance;
  }
  TextureManager(const TextureManager &) = delete;
  TextureManager &operator=(const TextureManager &) = delete;

  size_t load_texture(const std::string &path);

private:
  TextureManager() = default;

  std::unordered_map<std::string, size_t> cache_;
};

} // namespace skeleton::core
