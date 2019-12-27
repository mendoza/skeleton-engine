#include <Components.hpp>
#include <GameState.hpp>
#include <LuaHelperFunctions.hpp>
namespace Skeleton {

static Entity *loadEntity(sol::state L, gameDataRef data,
                          const std::string &type) {
  Entity e = data->entities.create();
  auto v = luah::getTableKeys(L, type);
  sol::table entityTable = L[type];
  for (auto &componentName : v) {
    if (componentName == "GraphicsComponent") {
      sol::table gcTable = entityTable["GraphicsComponent"];
      std::cout << "graphic" << std::endl;
    } else if (componentName == "NpcComponent") {
      sol::table npccTable = entityTable["NpcComponent"];
      std::cout << "" << std::endl;
    }
    std::cout << "Added " << componentName << " to " << type << std::endl;
  }
  return e;
}

GameState::GameState(gameDataRef data) {
  this->_data = data;
  this->script.script_file("scripts/game.lua");
  Entity *e = loadEntity(this->script.lua_state, this->_data, "player");

  sol::table player = script["player"]["graphicComponent"];
  this->entity = this->_data->entities.create();
  std::string sprite = player["sprite"];
  sf::Vector2f scale(player["scale"]["width"], player["scale"]["height"]);
  if (player["animation"]) {
    sf::Vector2u imageCount(player["animation"]["horizontalFrameCount"],
                            player["animation"]["verticalFrameCount"]);
    int row = player["animation"]["row"];
    this->entity.add<GraphicComponent>(this->_data, sprite, imageCount, scale,
                                       true, row);
  }
}
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
void GameState::draw(float dt) {
  this->_data->window.clear(sf::Color(125, 125, 125));
  this->entity.get<GraphicComponent>().draw();
  this->_data->window.display();
}
} // namespace Skeleton