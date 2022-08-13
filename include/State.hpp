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

	void setupEngineUserTypes() {
		sol::table skeleton = L.create_named_table("skeleton");
		skeleton.new_enum<sf::Keyboard::Key>("keyboard",
											 {{"right", sf::Keyboard::Right},
											  {"left", sf::Keyboard::Left},
											  {"space", sf::Keyboard::Space}});

		skeleton.new_enum<sf::Event::EventType>(
			"event_type",
			{{"key_pressed", sf::Event::EventType::KeyPressed},
			 {"key_released", sf::Event::EventType::KeyReleased}});

		sol::usertype<sf::Event> eventType = L.new_usertype<sf::Event>(
			"Event", sol::constructors<sf::Event()>());

		eventType["type"] = sol::readonly(&sf::Event::type);

		sol::usertype<sf::Event::KeyEvent> keyEventType =
			L.new_usertype<sf::Event::KeyEvent>(
				"KeyEvent", sol::constructors<sf::Event::KeyEvent()>());

		keyEventType["code"] = sol::readonly(&sf::Event::KeyEvent::code);

		eventType["key"] = sol::readonly(&sf::Event::key);
	}
	sol::state L;
	sf::Clock Clock;
	ConsoleWidget console;
	bool isOpen = false;
};
}; // namespace skeleton