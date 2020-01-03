#include <Game.hpp>
#include <SplashState.hpp>

namespace Skeleton {
Game::Game(int width, int height, std::string title, int limit) {
  _data->window.create(sf::VideoMode(width, height), title,);
  _data->window.setFramerateLimit(limit);
  _data->machine.addState(StateRef(new SplashState(this->_data)));
  this->run();
}

void Game::run() {
  float newTime, frametime, interpolation;
  float currentTime = this->_clock.getElapsedTime().asSeconds();
  float accumulator = 0.0f;
  while (this->_data->window.isOpen()) {
    this->_data->machine.processStateChanges();
    newTime = this->_clock.getElapsedTime().asSeconds();
    frametime = newTime - currentTime;

    if (frametime > 0.25f) {
      frametime = 0.25f;
    }
    currentTime = newTime;
    accumulator += frametime;
    while (accumulator >= dt) {
      this->_data->machine.getActiveState()->handleInput();
      this->_data->machine.getActiveState()->update(dt);
      accumulator -= dt;
    }

    interpolation = accumulator / dt;
    this->_data->machine.getActiveState()->draw(interpolation);
  }
}
} // namespace Skeleton