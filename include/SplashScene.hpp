#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include "SkeletonSceneManager.hpp"
#include "TestScene.hpp"
#include <Scene.hpp>
#include <SceneManager.hpp>
#include <ServiceLocator.hpp>
#include <SkeletonRenderer.hpp>

class SplashScene : public skeleton::Scene {

  public:
	SplashScene();
	~SplashScene() override;
	void on_init() override;
	void on_input(SDL_Event &event) override;
	void on_update(float dt) override;
	void on_draw() override;
	void on_destroy() override;
	void draw_debug_window() override;

  private:
	uint64_t start_time = SDL_GetPerformanceCounter();
	double time_to_change_scene = 5.0;
	sol::table config;
	sol::table splash;
	skeleton::ServiceLocator locator;
};

#endif