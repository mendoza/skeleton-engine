#ifndef SKELETON_SCENE_HPP
#define SKELETON_SCENE_HPP

#include <GameData.hpp>
#include <Logger.hpp>
#include <SDL2/SDL.h>
#include <Utils.hpp>
#include <memory>
#include <sol.hpp>
namespace skeleton {
class Scene {
  public:
	sol::state L;
	skeleton::Logger *logger;
	// ConsoleWidget console;
	bool is_open = false;
	Scene() { logger = skeleton::Logger::get_instance(); }
	~Scene() { logger->log("scene destroy"); }
	// User's Functions
	virtual void on_init() = 0;
	virtual void on_input(SDL_Event &event) = 0;
	virtual void on_update(float dt) = 0;
	virtual void on_draw() = 0;
	virtual void on_destroy() = 0;
	virtual void create_debug_window() = 0;

	// Engine's Functions
	virtual void pause() {}
	virtual void resume() {}
	virtual void init() {
		logger->log("scene init");
		on_init();
	}
	virtual void draw() { on_draw(); }
	virtual void handle_input(SDL_Event &event) { on_input(event); }
	virtual void update(float dt) { this->on_update(dt); }
	virtual void destroy() { this->on_destroy(); }

	virtual void set_engine_user_types() { skeleton::setEngineMetadata(L); }
};
typedef std::unique_ptr<Scene> SceneRef;

}; // namespace skeleton

#endif