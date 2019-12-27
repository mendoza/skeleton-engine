#pragma once
#include <Game.hpp>
#include <LuaScript.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>

namespace Skeleton {
class SplashState : public State {

public:
  SplashState(gameDataRef data);
  void init();
  void handleInput();
  void update(float dt);
  void draw(float dt);

private:
  gameDataRef _data;
  sf::Clock _clock;
  sf::Sprite _background;
  LuaScript script;
};
} // namespace Skeleton