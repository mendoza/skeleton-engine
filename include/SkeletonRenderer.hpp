#ifndef SKELETON_RENDER_SERVICE_HPP
#define SKELETON_RENDER_SERVICE_HPP
#include "AssetManager.hpp"
#include "Renderer.hpp"
#include <SDL2/SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>
namespace skeleton {
class SkeletonRenderer : public Renderer {
  public:
	SkeletonRenderer();
	SkeletonRenderer(std::string title, int width, int height, bool debug_mode);
	~SkeletonRenderer() override;
	void update() override;
	void clear() override;
	void shutdown() override;
	void draw_scene() override;
	void add_texture(std::string file_path, std::string name) override;
	void draw_texture(std::string name, SDL_Rect clip, int x, int y) override;
	void draw_rect(SDL_Color color, int x, int y, int w, int h) override;
	SDL_Texture *get_texture(std::string name) override;
	int get_window_width() override;
	int get_window_height() override;
	void set_clear_color(SDL_Color color) override;
	void set_debug_mode(bool debug_mode) override;

	bool debug_mode = false;
	SDL_Window *window;
	SDL_Renderer *renderer;
	AssetManager *asset_manager;
};
} // namespace skeleton
#endif