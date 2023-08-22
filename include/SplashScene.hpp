#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include <GameData.hpp>
#include <Scene.hpp>
#include <SceneManager.hpp>
#include <ServiceLocator.hpp>
#include <SkeletonRenderer.hpp>
#include <Spritesheet.hpp>

class SplashScene : public skeleton::Scene {

  public:
	SplashScene();
	~SplashScene();
	void on_init();
	void on_input(SDL_Event &event);
	void on_update(float dt);
	void on_draw();
	void on_destroy();
	void create_debug_window();

  private:
	SDL_Surface *background;
	uint64_t initial_time = SDL_GetPerformanceCounter();
	sol::table config;
	sol::table splash;
	skeleton::ServiceLocator locator;
};

#endif