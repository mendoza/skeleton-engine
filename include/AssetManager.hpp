#ifndef ASSET_MANAGER_SERVICE_HPP
#define ASSET_MANAGER_SERVICE_HPP

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <Service.hpp>
#include <map>
#include <string>

namespace skeleton {
class AssetManager : public Service {

  public:
	AssetManager() {}

	virtual void add_texture(std::string name, std::string file_name) = 0;
	virtual SDL_Texture *get_texture(std::string name) = 0;
};
}; // namespace skeleton

#endif