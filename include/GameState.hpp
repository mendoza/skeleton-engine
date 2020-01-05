#pragma once
#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>

namespace Skeleton {
class GameState : public State {

public:
  GameState(gameDataRef data);
  void init() override;
  void handleInput() override;
  void update(float dt) override;
  void draw() override;

private:
  gameDataRef _data;
  sf::Clock _clock;
  sf::Sprite _background;
  sol::state script;
  Entity entity;
  EntityManager entities;
  SystemManager systems;
};
} // namespace Skeleton