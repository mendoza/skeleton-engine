#pragma once
#include <Engine.hpp>

class SplashState : public Skeleton::State {

  public:
	SplashState(Skeleton::GameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw();

  private:
	Skeleton::GameDataRef Data;
	sf::Clock Clock;
	sf::Sprite Background;
	sol::state Script;
	sol::table Meta;
	sol::table Splash;
};