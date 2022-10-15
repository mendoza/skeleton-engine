#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include <Actor.hpp>
#include <Components.hpp>
#include <ConsoleWidget.hpp>
#include <OpenECS.hpp>
#include <SFML/Window/Event.hpp>
#include <State.hpp>
#include <Systems.hpp>
#include <sol.hpp>

class TestState : public skeleton::State {
  public:
	TestState(skeleton::GameDataRef Data);
	void onInit();
	void onInput(sf::Event event);
	void onUpdate(float dt);
	void onDraw(float dt);
	void setupDebugWindow();
	void setupLuaState();
	void execCommand(std::string scriptString);

  private:
	sf::Sprite Background;
	ecs::EntityManager Actors;
	ecs::SystemManager Systems = ecs::SystemManager(Actors);
	sol::function on_update;
	sol::function handle_input;
};

#endif