#include <Components.hpp>
#include <GameState.hpp>
#include <LuaHelper.hpp>
#include <Systems.hpp>
namespace Skeleton {
GameState::GameState(gameDataRef data) : systems(entities) {
  this->_data = data;
  this->script.script_file("scripts/player.lua");
  sol::table player = script["player"];
  this->entity = this->entities.create();
  this->entity.add<GraphicComponent>(this->_data, player["graphicComponent"]);
  this->systems.add<drawGraphicSystem>(this->_data);
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
  this->_data->window.clear(sf::Color(125, 125, 125));
  this->systems.update(dt);
}

void GameState::draw() { this->_data->window.display(); }
} // namespace Skeleton