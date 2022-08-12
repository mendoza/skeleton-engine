#pragma once
#include <ConsoleWidget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <sol.hpp>
namespace skeleton {
class State {
  public:
	virtual void init() = 0;
	virtual void handleInput(sf::Event event) = 0;
	virtual void update(float dt) = 0;
	virtual void draw(float dt) = 0;
	virtual void drawDebugWindow() = 0;

	virtual void pause() {}
	virtual void resume() {}
	sol::state L;
	sf::Clock Clock;
	ConsoleWidget console;
	bool isOpen = false;
};
}; // namespace skeleton