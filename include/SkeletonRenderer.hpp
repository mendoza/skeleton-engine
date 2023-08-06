#ifndef SKELETON_RENDER_SERVICE_HPP
#define SKELETON_RENDER_SERVICE_HPP
#include <Renderer.hpp>
#include <SDL2/SDL.h>

namespace skeleton {
class SkeletonRenderer : public Renderer {
  public:
	SkeletonRenderer();
	SkeletonRenderer(SDL_Window *window, SDL_Renderer *renderer);
	~SkeletonRenderer();
	SDL_Window *window;
	SDL_Renderer *renderer;
	void drawSprite(Spritesheet *spritesheet, int x, int y);
	void update();
	void clear();
};
} // namespace skeleton
#endif