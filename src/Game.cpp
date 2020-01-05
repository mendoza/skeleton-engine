#include <Game.hpp>
#include <SplashState.hpp>

namespace Skeleton {
Game::Game(int width, int height, std::string title, std::string iconFile,
           int limit) {
  sf::Image image;
  image.loadFromFile(iconFile);
  _data->window.create(sf::VideoMode(width, height), title);
  _data->window.setIcon(image.getSize().x, image.getSize().y,
                        image.getPixelsPtr());
  _data->window.setFramerateLimit(limit);
  _data->machine.addState(StateRef(new SplashState(this->_data)));
  this->run();
}

void Game::run() {
  float frametime;
  float accumulator = 0.0f;
  while (this->_data->window.isOpen()) {
    this->_data->machine.processStateChanges();

    while (accumulator > dt) {
      accumulator -= dt;
      this->_data->machine.getActiveState()->handleInput();
      this->_data->machine.getActiveState()->update(dt);
    }

    frametime = this->_clock.restart().asSeconds();
    accumulator += frametime;
    // printf("FPS: %d\n", (int)(1.0f / frametime));
    this->_data->machine.getActiveState()->draw();
  }
}
} // namespace Skeleton