#ifndef SKELETON_UTILS_HPP
#define SKELETON_UTILS_HPP

#include <Logger.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <sol.hpp>
namespace skeleton {

inline void setENgineUserTypes(sol::state &L) {
	sol::table skeleton = L.create_named_table("skeleton");
	skeleton.new_enum<sf::Keyboard::Key>("keyboard",
										 {{"right", sf::Keyboard::Right},
										  {"left", sf::Keyboard::Left},
										  {"space", sf::Keyboard::Space}});

	skeleton.new_enum<sf::Event::EventType>(
		"event_type", {{"key_pressed", sf::Event::EventType::KeyPressed},
					   {"key_released", sf::Event::EventType::KeyReleased}});

	sol::usertype<sf::Event> eventType =
		L.new_usertype<sf::Event>("Event", sol::constructors<sf::Event()>());

	eventType["type"] = sol::readonly(&sf::Event::type);

	sol::usertype<sf::Event::KeyEvent> keyEventType =
		L.new_usertype<sf::Event::KeyEvent>(
			"KeyEvent", sol::constructors<sf::Event::KeyEvent()>());

	keyEventType["code"] = sol::readonly(&sf::Event::KeyEvent::code);

	eventType["key"] = sol::readonly(&sf::Event::key);

	sol::usertype<sf::Vector2f> sfVector2f = L.new_usertype<sf::Vector2f>(
		"vector_2f",
		sol::constructors<sf::Vector2f(), sf::Vector2f(float, float)>(), "x",
		&sf::Vector2f::x, "y", &sf::Vector2f::y);
}

inline void setLogger(sol::state &L) {

	sol::usertype<skeleton::Logger> loggerUserType =
		L.new_usertype<skeleton::Logger>("Logger");

	loggerUserType["log"] = &skeleton::Logger::Log;
	loggerUserType["warning"] = &skeleton::Logger::Warning;
	loggerUserType["error"] = &skeleton::Logger::Error;
	loggerUserType["create"] = &skeleton::Logger::getInstance;

	skeleton::Logger *logger = logger->getInstance();

	L["console"] = logger;
}
} // namespace skeleton

#endif