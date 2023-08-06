#ifndef SKELETON_ENGINE_HPP
#define SKELETON_ENGINE_HPP

#include <GameData.hpp>
#include <SDL2/SDL.h>
#include <SceneManager.hpp>
#include <ServiceLocator.hpp>
#include <SkeletonRenderer.hpp>
#include <chrono>

namespace skeleton {

class Engine {
  public:
	Engine(bool debug_mode = false);
	void build_window(uint32_t width, uint32_t height, std::string Title,
					  std::string IconFile, bool fullscreen);

  private:
	GameDataRef data = std::make_shared<GameData>();
	void run();
	ServiceLocator locator;
};
}; // namespace skeleton

#endif