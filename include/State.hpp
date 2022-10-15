#ifndef SKELETON_STATE_HPP
#define SKELETON_STATE_HPP

#include <ConsoleWidget.hpp>
#include <GameData.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <Utils.hpp>
#include <sol.hpp>

namespace skeleton {
class State {

  public:
	skeleton::GameDataRef Data;
	sol::state L;
	sf::Clock Clock;
	ConsoleWidget console;
	bool isOpen = false;

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
	virtual void init() { onInit(); }
	virtual void draw(float dt) { onDraw(dt); }
	virtual void handleInput() {
		sf::Event event;
		while (this->Data->Window.pollEvent(event)) {
			onInput(event);

			switch (event.type) {
			case sf::Event::Closed:
				this->Data->Window.close();
				break;

			case sf::Event::Resized:
				sf::FloatRect visibleArea(0, 0, event.size.width,
										  event.size.height);
				this->Data->Window.setView(sf::View(visibleArea));
				break;

			default:
				break;
			}
		}
	}
	virtual void update(float dt);
	virtual void setupEngineUserTypes();
};
}; // namespace skeleton

#endif