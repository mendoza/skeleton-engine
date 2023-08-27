#ifndef SKELETON_RENDER_SERVICE_HPP
#define SKELETON_RENDER_SERVICE_HPP
#include "AssetManager.hpp"
#include "Renderer.hpp"
#include <SDL2/SDL.h>
namespace skeleton {
class SkeletonRenderer : public Renderer {
  public:
	SkeletonRenderer();
	SkeletonRenderer(SDL_Window *window, SDL_Renderer *renderer);
	~SkeletonRenderer();
	void update();
	void clear();
	void shutdown();
	void add_texture(std::string file_path, std::string name);
	void draw_texture(std::string name, SDL_Rect *clip, int x, int y);
	SDL_Texture *get_texture(std::string name);

	SDL_Window *window;
	SDL_Renderer *renderer;
	AssetManager *asset_manager;
};
} // namespace skeleton
#endif