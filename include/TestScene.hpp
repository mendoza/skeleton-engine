#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include <Actor.hpp>
#include <Components.hpp>
#include <OpenECS.hpp>
#include <SDL2/SDL.h>
#include <Scene.hpp>
#include <Systems.hpp>
#include <sol.hpp>
class TestScene : public skeleton::Scene {
  public:
	TestScene();
	~TestScene();
	void on_init();
	void on_input(SDL_Event &event);
	void on_update(float dt);
	void on_draw();
	void on_destroy();
	void create_debug_window();
	void setupLuaState();

  private:
	SDL_Surface *background;
	ecs::EntityManager Actors;
	ecs::SystemManager Systems = ecs::SystemManager(Actors);
	sol::function script_on_update;
	sol::function script_handle_input;
	skeleton::Spritesheet *spritesheet;
};

#endif