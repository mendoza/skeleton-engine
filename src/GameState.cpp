#include <Components.hpp>
#include <GameState.hpp>
#include <LuaHelper.hpp>
namespace Skeleton {
GameState::GameState(gameDataRef data) {
  this->_data = data;
  this->script.script_file("scripts/player.lua");
  sol::table player = script["player"]["graphicComponent"];
  this->entity = this->_data->entities.create();
  std::string sprite = player["sprite"];
  std::string name = player["spriteName"];
  sf::Vector2f scale(player["scale"]["width"], player["scale"]["height"]);
  if (player["animation"]) {
    sf::Vector2u imageCount(player["animation"]["horizontalFrameCount"],
                            player["animation"]["verticalFrameCount"]);
    int row = player["animation"]["row"];
    this->entity.add<GraphicComponent>(this->_data, name, sprite, imageCount,
                                       scale, true, row);
  }
}
void GameState::init() {}
void GameState::handleInput() {
  sf::Event event;
  while (this->_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->_data->window.close();
    }
    if (event.key.code == sf::Keyboard::Space) {
    }
  }
}
void GameState::update(float dt) {
  this->entity.get<GraphicComponent>().update(
      this->_clock.restart().asSeconds());
}
void GameState::draw(float dt) {
  this->_data->window.clear(sf::Color(125, 125, 125));
  this->entity.get<GraphicComponent>().draw();
  this->_data->window.display();
}
} // namespace Skeleton