#pragma once
#include <Engine.hpp>

class SplashState : public skeleton::State {

  public:
	SplashState(skeleton::GameDataRef data);
	void init();
	void handleInput(sf::Event event);
	void update(float dt);
	void drawDebugWindow();
	void draw(float dt );

  private:
	skeleton::GameDataRef Data;
	sf::Clock Timer;
	sf::Sprite Background;
	sol::table config;
	sol::table Splash;
};