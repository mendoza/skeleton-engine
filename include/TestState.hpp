
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

  private:
	skeleton::GameDataRef Data;
	sf::Sprite Background;
	ecs::EntityManager Actors;
	ecs::SystemManager Systems;
};