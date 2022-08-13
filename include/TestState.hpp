
#pragma once
#include <Actor.hpp>
#include <Engine.hpp>
class TestState : public skeleton::State {

  public:
	TestState(skeleton::GameDataRef Data);
	void init();
	void handleInput(sf::Event event);
	void update(float dt);
	void draw(float dt);
	void drawDebugWindow();
	void setupLuaState();
	void execCommand(std::string scriptString);

  private:
	skeleton::GameDataRef Data;
	sf::Sprite Background;
	ecs::EntityManager Actors;
	ecs::SystemManager Systems;
	sol::function on_update;
	sol::function handle_input;
};