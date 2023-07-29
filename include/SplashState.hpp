#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include <GameData.hpp>
#include <State.hpp>
#include <StateMachine.hpp>
class SplashState : public skeleton::State {

  public:
	SplashState(skeleton::GameDataRef data);
	void on_init();
	void on_input(SDL_Event &event);
	void on_update(float dt);
	void on_draw();
	void create_debug_window();

  private:
	SDL_Surface *background;
	uint64_t initial_time = SDL_GetPerformanceCounter();
	sol::table config;
	sol::table splash;
};

#endif