#pragma once
#include <ConsoleWidget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <Utils.hpp>
#include <sol.hpp>

namespace skeleton {
class GameData;
typedef std::shared_ptr<GameData> GameDataRef;
class State {
  public:
	State(skeleton::GameDataRef data) : Data(data) {}
	// User's Functions
	virtual void onInit() = 0;
	virtual void onInput(sf::Event event) = 0;
	virtual void onUpdate(float dt) = 0;
	virtual void onDraw(float dt) = 0;
	virtual void setupDebugWindow() = 0;

	// Engine's Functions
	virtual void pause() {}
	virtual void resume() {}
	virtual void init();
	virtual void draw(float dt);
	virtual void handleInput();
	virtual void update(float dt);
	virtual void setupEngineUserTypes();

  public:
	skeleton::GameDataRef Data;
	sol::state L;
	sf::Clock Clock;
	ConsoleWidget console;
	bool isOpen = false;
};
}; // namespace skeleton