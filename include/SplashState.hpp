#pragma once
#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>

namespace Skeleton {
class SplashState : public State {

public:
  SplashState(gameDataRef data);
  void init();
  void handleInput();
  void update(float dt);
  void draw();

private:
  gameDataRef _data;
  sf::Clock _clock;
  sf::Sprite _background;
  sol::state script;
  sol::table meta;
  sol::table splash;
};
} // namespace Skeleton