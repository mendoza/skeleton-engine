#include "SkeletonAssetsManager.hpp"

namespace skeleton {
SkeletonAssetsManager::SkeletonAssetsManager() {}

SkeletonAssetsManager::~SkeletonAssetsManager() {
	for (auto &&p : this->textures) {
		SDL_DestroyTexture(p.second);
	}
	this->textures.clear();
}

void SkeletonAssetsManager::add_texture(std::string name,
										std::string file_name) {
	SDL_Surface *surf = IMG_Load(file_name.c_str());
	ServiceLocator locator;
	SDL_Texture *text = SDL_CreateTextureFromSurface(
		locator.get<SkeletonRenderer>()->renderer, surf);

	if (this->textures.find(name) == this->textures.end()) {
		this->textures[name] = text;
	}
	SDL_FreeSurface(surf);
}

SDL_Texture *SkeletonAssetsManager::get_texture(std::string name) {
	return this->textures.at(name);
}
} // namespace skeleton
