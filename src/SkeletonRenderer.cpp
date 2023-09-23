#include "SkeletonRenderer.hpp"

namespace skeleton {
SkeletonRenderer::SkeletonRenderer() {
	this->window = nullptr;
	this->renderer = nullptr;
	this->asset_manager = new AssetManager();
	logger->log("Created Renderer Service");
}

SkeletonRenderer::SkeletonRenderer(SDL_Window *window, SDL_Renderer *renderer) {
	this->window = window;
	this->renderer = renderer;
	this->asset_manager = new AssetManager();
	logger->log("Created Renderer Service");
}

SkeletonRenderer::~SkeletonRenderer() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	delete this->asset_manager;
	logger->log("Destroyed Renderer service");
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

	SDL_RenderCopy(this->renderer, asset_manager->get_texture(name), nullptr,
				   nullptr);
}

void SkeletonRenderer::draw_rect(SDL_Color color, int x, int y, int w, int h) {
	SDL_Rect rect = {x, y, w, h};
	SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(this->renderer, &rect);
}
int SkeletonRenderer::get_window_width() {
	int w, h;
	SDL_GetWindowSize(this->window, &w, &h);
	return w;
}

int SkeletonRenderer::get_window_height() {
	int w, h;
	SDL_GetWindowSize(this->window, &w, &h);
	return h;
}
void SkeletonRenderer::set_clear_color(SDL_Color color) {
	SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}
} // namespace skeleton