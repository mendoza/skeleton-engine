
#pragma once
#include <Actor.hpp>
#include <Engine.hpp>
class TestState : public skeleton::State {

  public:
	TestState(skeleton::GameDataRef Data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);
	void setupLuaState();

  private:
	skeleton::GameDataRef Data;
	sf::Sprite Background;
	ecs::EntityManager Actors;
	ecs::SystemManager Systems;
	sol::function state_update;
	sol::function state_handle_input;
};