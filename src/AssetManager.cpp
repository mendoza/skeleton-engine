#include "AssetManager.hpp"

namespace skeleton {
AssetManager::AssetManager() {}

AssetManager::~AssetManager() {
	for (auto &&p : this->textures) {
		SDL_DestroyTexture(p.second);
	}
	this->textures.clear();
}

void AssetManager::add_texture(const std::string& file_path, const std::string& name,
							   SDL_Renderer *renderer) {
	SDL_Surface *surf = IMG_Load(file_path.c_str());
	SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
	std::size_t hash = hasher(name);
	if (this->textures.find(hash) == this->textures.end()) {
		this->textures[hash] = text;
	}
	SDL_FreeSurface(surf);
	logger->logf("Successfully added %s (%zu)\n", name.c_str(), hash);
}

SDL_Texture *AssetManager::get_texture(const std::string& name) {
	return this->textures.at(hasher(name));
}
} // namespace skeleton
