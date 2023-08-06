#include <SkeletonAssetsManager.hpp>

namespace skeleton {
SkeletonAssetsManager::SkeletonAssetsManager() {}

SkeletonAssetsManager::~SkeletonAssetsManager() {}

void SkeletonAssetsManager::add_surface(std::string name,
										std::string file_name) {
	SDL_Surface *surf = IMG_Load(file_name.c_str());
	if (this->surfaces.find(name) == this->surfaces.end()) {
		this->surfaces[name] = surf;
	}
}

SDL_Surface *SkeletonAssetsManager::get_surface(std::string name) {
	return this->surfaces.at(name);
}
} // namespace skeleton
