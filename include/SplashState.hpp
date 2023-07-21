#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include <GameData.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <State.hpp>
#include <StateMachine.hpp>
class SplashState : public skeleton::State {

  public:
	SplashState(skeleton::GameDataRef data);
	void on_init();
	void on_input(sf::Event event);
	void on_update(float dt);
	void on_draw();
	void create_debug_window();

  private:
	sf::Sprite background;
	sol::table config;
	sol::table splash;
};

#endif