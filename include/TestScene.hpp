#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include "Actor.hpp"
#include "Components.hpp"
#include "Scene.hpp"
#include "SkeletonRenderer.hpp"
#include "Systems.hpp"
#include "OpenECS.hpp"
#include <SDL2/SDL.h>
#include <sol/sol.hpp>
class TestScene : public skeleton::Scene {
  public:
	TestScene();
	~TestScene();
	void on_init();
	void on_input(SDL_Event &event);
	void on_update(float dt);
	void on_draw();
	void on_destroy();
	void draw_debug_window();
	void setupLuaState();

  private:
	SDL_Surface *background;
	ecs::EntityManager entities;
	ecs::SystemManager Systems = ecs::SystemManager(entities);
	sol::function script_on_update;
	sol::function script_handle_input;
};

#endif