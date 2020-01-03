#include <Components.hpp>
#include <GameState.hpp>
#include <LuaHelper.hpp>
namespace Skeleton {
GameState::GameState(gameDataRef data) {
  this->_data = data;
  this->script.script_file("scripts/player.lua");
  sol::table player = script["player"];
  this->entity = this->entities.create();
  this->entity.add<GraphicComponent>(this->_data, player["graphicComponent"]);
}
// GameState::~GameState() { }
void GameState::init() {}
void GameState::handleInput() {
  sf::Event event;
  while (this->_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->_data->window.close();
    }
  }
}
void GameState::update(float dt) {
  this->entity.get<GraphicComponent>().update(
      this->_clock.restart().asSeconds());
}
void GameState::draw() {
  this->_data->window.clear(sf::Color(125, 125, 125));
  this->entity.get<GraphicComponent>().draw();
  this->_data->window.display();
}
} // namespace Skeleton