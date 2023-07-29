#ifndef SKELETON_ASSET_MANAGER_HPP
#define SKELETON_ASSET_MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <map>
#include <string>

namespace skeleton {
class AssetManager {

  public:
	AssetManager() {}
	~AssetManager() {
		// go key by key removing surfaces

		for (const auto &myPair : this->surfaces) {
			SDL_FreeSurface(myPair.second);
		}
	}

	void add_surface(std::string name, std::string file_name);
	SDL_Surface *get_surface(std::string name);

  private:
	std::map<std::string, SDL_Surface *> surfaces;
};
}; // namespace skeleton

#endif