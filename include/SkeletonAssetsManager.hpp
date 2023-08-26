#ifndef SKELETON_ASSETS_MANAGER_SERVICE_HPP
#define SKELETON_ASSETS_MANAGER_SERVICE_HPP
#include "AssetManager.hpp"
#include "ServiceLocator.hpp"
#include "SkeletonRenderer.hpp"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>

namespace skeleton {
class SkeletonAssetsManager : public AssetManager {
  public:
	SkeletonAssetsManager();
	~SkeletonAssetsManager();
	void add_texture(std::string name, std::string file_name);
	SDL_Texture *get_texture(std::string name);
	std::map<std::string, SDL_Texture *> textures;
};
} // namespace skeleton
#endif