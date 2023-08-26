#ifndef SKELETON_ENGINE_HPP
#define SKELETON_ENGINE_HPP

#include <GameData.hpp>
#include <SDL2/SDL.h>
#include <SceneManager.hpp>
#include <ServiceLocator.hpp>
#include <SkeletonAssetsManager.hpp>
#include <SkeletonRenderer.hpp>
#include <SkeletonSceneManager.hpp>
#include <chrono>

namespace skeleton {

class Engine {
  private:
	bool is_running = true;
	bool debug_mode = true;
	ServiceLocator locator;

  public:
	Engine(bool debug_mode = false);
	~Engine();
	void build_window(uint32_t width, uint32_t height, std::string Title,
					  std::string IconFile, bool fullscreen);
	void run();
};
}; // namespace skeleton

#endif