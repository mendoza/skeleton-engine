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
	~SkeletonRenderer() override;
	void update() override;
	void clear() override;
	void shutdown() override;
	void add_texture(std::string file_path, std::string name) override;
	void draw_texture(std::string name, SDL_Rect *clip, int x, int y) override;
	SDL_Texture *get_texture(std::string name) override;

	SDL_Window *window;
	SDL_Renderer *renderer;
	AssetManager *asset_manager;
};
} // namespace skeleton
#endif