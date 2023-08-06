#ifndef SKELETON_ASSETS_MANAGER_SERVICE_HPP
#define SKELETON_ASSETS_MANAGER_SERVICE_HPP
#include <AssetManager.hpp>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>

namespace skeleton {
class SkeletonAssetsManager : public AssetManager {
  public:
	SkeletonAssetsManager();
	~SkeletonAssetsManager();
	void add_surface(std::string name, std::string file_name);
	SDL_Surface *get_surface(std::string name);
	std::map<std::string, SDL_Surface *> surfaces;
};
} // namespace skeleton
#endif