#include "SkeletonRenderer.hpp"

namespace skeleton {
SkeletonRenderer::SkeletonRenderer() {
	this->window = NULL;
	this->renderer = NULL;
	this->asset_manager = new AssetManager();
}

SkeletonRenderer::SkeletonRenderer(SDL_Window *window, SDL_Renderer *renderer) {
	this->window = window;
	this->renderer = renderer;
	this->asset_manager = new AssetManager();
}

SkeletonRenderer::~SkeletonRenderer() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

void SkeletonRenderer::update() { SDL_RenderPresent(this->renderer); }

void SkeletonRenderer::clear() {
	SDL_SetRenderDrawColor(this->renderer, 125, 125, 125, 255);
	SDL_RenderClear(this->renderer);
}

void SkeletonRenderer::shutdown() {
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void SkeletonRenderer::add_texture(std::string file_path, std::string name) {
	this->asset_manager->add_texture(file_path, name, this->renderer);
}

SDL_Texture *SkeletonRenderer::get_texture(std::string name) {
	return this->asset_manager->get_texture(name);
}

void SkeletonRenderer::draw_texture(std::string name, SDL_Rect *clip, int x,
									int y) {

	SDL_RenderCopy(this->renderer, asset_manager->get_texture(name), NULL,
				   NULL);
}
} // namespace skeleton