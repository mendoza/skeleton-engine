#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include <GameData.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <State.hpp>
class SplashState : public skeleton::State {

  public:
	SplashState(skeleton::GameDataRef data);
	void onInit();
	void onInput(sf::Event event);
	void onUpdate(float dt);
	void onDraw(float dt);
	void setupDebugWindow();

  private:
	sf::Sprite Background;
	sol::table config;
	sol::table Splash;
};

#endif