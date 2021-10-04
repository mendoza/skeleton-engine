
#pragma once
#include <Engine.hpp>
#include <Actor.hpp>
class TestState : public Skeleton::State {

  public:
	TestState(Skeleton::GameDataRef Data);
	void init();
	void handleInput();
	void update(float dt);
	void draw();

  private:
	Skeleton::GameDataRef Data;
	sf::Sprite Background;
    Actor actor;
	ecs::EntityManager Actors;
	ecs::SystemManager GraphicsSystem;
	ecs::SystemManager OthersSystem;
};