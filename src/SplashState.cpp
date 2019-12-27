#include <GameState.hpp>
#include <SplashState.hpp>
#include <iostream>

namespace Skeleton {
SplashState::SplashState(gameDataRef data)
    : _data(data), script(LuaScript(("scripts/game.lua"))) {}

void SplashState::init() {
  std::string filePath =
      this->script.get<std::string>("splash.backgroundImageFile");
  this->_data->assets.loadTexture("Splash State Background", filePath);
  _background.setTexture(
      this->_data->assets.getTexture("Splash State Background"));
}

void SplashState::handleInput() {
  sf::Event event;
  while (this->_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->_data->window.close();
    }
  }
}

void SplashState::update(float dt) {
  float time = this->script.get<float>("splash.time");
  if (this->_clock.getElapsedTime().asSeconds() > time) {
    this->_data->machine.addState(StateRef(new GameState(this->_data)));
  }
}

void SplashState::draw(float dt) {
  int r = this->script.get<int>("splash.background.r");
  int g = this->script.get<int>("splash.background.g");
  int b = this->script.get<int>("splash.background.b");
  this->_data->window.clear(sf::Color(r, g, b));
  this->_data->window.draw(this->_background);
  this->_data->window.display();
}
} // namespace Skeleton