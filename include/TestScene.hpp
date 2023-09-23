#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include "Components.hpp"
#include "Scene.hpp"
#include "SkeletonRenderer.hpp"
#include "Systems.hpp"
#include <SDL2/SDL.h>
#include <ctime>
#include <random>
#include <sol/sol.hpp>
class TestScene : public skeleton::Scene {
  public:
	TestScene(std::string tag);
	~TestScene() override;
	void on_init() override;
	void on_input(SDL_Event &event) override;
	void on_update(float dt) override;
	void on_draw() override;
	void on_destroy() override;
	void draw_debug_window() override;
	void setupLuaState();

  private:
	// flecs::world ecs;
	// initiante a matrix of ints
	int *world;
	int cellSize = 10;
	int numCellsWidth = -1;
	int numCellsHeight = -1;
	SDL_Surface *background;
	sol::function script_on_update;
	sol::function script_handle_input;
};

#endif