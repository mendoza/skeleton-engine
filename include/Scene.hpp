#ifndef SKELETON_SCENE_HPP
#define SKELETON_SCENE_HPP

#include "AssetManager.hpp"
#include "Logger.hpp"
#include "ServiceLocator.hpp"
#include "Utils.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <sol/sol.hpp>
namespace skeleton {
class Scene {
  protected:
	sol::state L;
	skeleton::Logger *logger = skeleton::Logger::get_instance();
	skeleton::ServiceLocator locator;
	skeleton::AssetManager *asset_manager;

	// User's Functions
	virtual void on_init() = 0;
	virtual void on_input(SDL_Event &event) = 0;
	virtual void on_update(float dt) = 0;
	virtual void on_draw() = 0;
	virtual void on_destroy() = 0;

  public:
	bool is_open = false;
	Scene() { asset_manager = new AssetManager(); }
	~Scene() { delete asset_manager; }

	// Engine's Functions
	virtual void pause() {}
	virtual void resume() {}
	virtual void init() {
		logger->log("scene init");
		this->on_init();
	}
	virtual void draw() { this->on_draw(); }
	virtual void handle_input(SDL_Event &event) { this->on_input(event); }
	virtual void update(float dt) { this->on_update(dt); }
	virtual void destroy() {
		logger->log("scene destroy");
		this->on_destroy();
	}
	virtual void draw_debug_window() = 0;
};
typedef std::unique_ptr<Scene> SceneRef;

}; // namespace skeleton

#endif