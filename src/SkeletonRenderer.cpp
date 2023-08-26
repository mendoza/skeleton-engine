#include <SkeletonRenderer.hpp>

namespace skeleton {
SkeletonRenderer::SkeletonRenderer() {
	this->window = NULL;
	this->renderer = NULL;
}

SkeletonRenderer::SkeletonRenderer(SDL_Window *window, SDL_Renderer *renderer) {
	this->window = window;
	this->renderer = renderer;
}

SkeletonRenderer::~SkeletonRenderer() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

void SkeletonRenderer::drawSpritesheet(Spritesheet *spritesheet, int x, int y) {
	SDL_Rect *position = new SDL_Rect();
	position->x = x;
	position->y = y;
	position->h = spritesheet->get_sprite_clip()->h;
	position->w = spritesheet->get_sprite_clip()->w;
	spritesheet->draw_selected_sprite(this->renderer, position);
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
} // namespace skeleton