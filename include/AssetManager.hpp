#ifndef SKELETON_ASSET_MANAGER_HPP
#define SKELETON_ASSET_MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <Service.hpp>
#include <map>
#include <string>

namespace skeleton {
class AssetManager : public Service {

  public:
	AssetManager() {}

	virtual void add_surface(std::string name, std::string file_name) = 0;
	virtual SDL_Surface *get_surface(std::string name) = 0;
};
}; // namespace skeleton

#endif