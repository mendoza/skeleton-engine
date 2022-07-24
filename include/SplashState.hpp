#pragma once
#include <Engine.hpp>

class SplashState : public skeleton::State {

  public:
	SplashState(skeleton::GameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt );

  private:
	skeleton::GameDataRef Data;
	sf::Clock Timer;
	sf::Sprite Background;
	sol::state Script;
	sol::table Meta;
	sol::table Splash;
};