#ifndef SKELETON_SCENE_HPP
#define SKELETON_SCENE_HPP

#include "AssetManager.hpp"
#include "Logger.hpp"
#include "ScriptManager.hpp"
#include "ServiceLocator.hpp"
#include "Utils.hpp"
#include <SDL2/SDL.h>
#include <flecs.h>
#include <memory>
#include <sol/sol.hpp>

namespace skeleton {
class Scene {
  protected:
	std::string tag;
	bool debug_mode;
	skeleton::Logger *logger = skeleton::Logger::get_instance();
	skeleton::AssetManager *asset_manager;
	skeleton::ScriptManager *script_manager;
	flecs::world ecs;
	// User's Functions
	virtual void on_init() = 0;
	virtual void on_input(SDL_Event &event) = 0;
	virtual void on_update(float dt) = 0;
	virtual void on_draw() = 0;
	virtual void on_destroy() = 0;

  public:
	Scene(std::string tag) : tag(tag) {
		asset_manager = new AssetManager();
		script_manager = new ScriptManager();
	}
	virtual ~Scene() {
		delete asset_manager;
		delete script_manager;
	}

	// Engine's Functions
	virtual void pause() {}
	virtual void resume() {}
	virtual void init() {
		logger->logf("[%s] Scene Init\n", tag.c_str());
		this->on_init();
	}
	virtual void draw() {
		skeleton::ServiceLocator::get<SkeletonRenderer>()->clear();
		this->on_draw();
		this->draw_debug_window();
		skeleton::ServiceLocator::get<SkeletonRenderer>()->update();
	}

	virtual void handle_input(SDL_Event event) { this->on_input(event); }
	virtual void update(float dt) { this->on_update(dt); }
	virtual void destroy() {
		logger->logf("[%s] Scene Destroy\n", tag.c_str());
		this->on_destroy();
	}
	virtual void draw_debug_window() = 0;
};
typedef std::unique_ptr<Scene> SceneRef;

}; // namespace skeleton

#endif