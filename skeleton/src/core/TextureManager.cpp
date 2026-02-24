#include <SDL_image.h>
#include <skeleton/core/Logger.hpp>
#include <skeleton/core/TextureManager.hpp>
#include <skeleton/graphics/Renderer.hpp>

namespace skeleton::core {

size_t TextureManager::load_texture(const std::string &path) {
  auto it = cache_.find(path);
  if (it != cache_.end())
    return it->second;

  auto &r = skeleton::graphics::Renderer::get_instance();
  SDL_Texture *tex = IMG_LoadTexture(r.get_sdl_renderer(), path.c_str());
  if (!tex) {
    Logger::error("Failed to load texture: " + path + " — " + IMG_GetError());
    return 0;
  }

  size_t key = std::hash<std::string>{}(path);
  r.store_texture(key, tex);
  cache_[path] = key;
  Logger::info("Loaded texture: " + path);
  return key;
}

} // namespace skeleton::core
