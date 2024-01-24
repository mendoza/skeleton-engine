#ifndef SKELETON_ENGINE_HPP
#define SKELETON_ENGINE_HPP

#include "SceneManager.hpp"
#include "ServiceLocator.hpp"
#include "SkeletonRenderer.hpp"
#include "SkeletonSceneManager.hpp"
#include <SDL2/SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <chrono>
#include <imgui.h>
#include <string.h>

namespace skeleton {

class Engine {
  private:
	bool is_running = true;
	bool debug_mode = true;

  public:
	Engine(bool debug_mode);
	~Engine();
	void build_window(int width, int height, const std::string &Title,
					  const std::string &IconFile, bool fullscreen);
	void run();
};
}; // namespace skeleton

#endif
