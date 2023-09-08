
#ifndef SKELETON_ASSETS_MANAGER_SERVICE_HPP
#define SKELETON_ASSETS_MANAGER_SERVICE_HPP
#include "Logger.hpp"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <functional>
#include <map>
#include <string>

namespace skeleton {
class AssetManager {
  public:
	AssetManager();
	~AssetManager();
	void add_texture(const std::string& file_path, const std::string& name,
					 SDL_Renderer *renderer);
	SDL_Texture *get_texture(const std::string& name);
	std::map<std::size_t, SDL_Texture *> textures;
	std::hash<std::string> hasher;
	skeleton::Logger *logger = skeleton::Logger::get_instance();
};
} // namespace skeleton
#endif