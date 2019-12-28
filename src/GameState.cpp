#include <Components.hpp>
#include <GameState.hpp>
namespace Skeleton {
void printTable(sol::table tab) {
  for (const auto &key_value_pair : tab) {
    sol::object key = key_value_pair.first;
    sol::object value = key_value_pair.second;
    std::string k = key.as<std::string>();
    sol::type t = value.get_type();
    switch (t) {
    case sol::type::string: {
      std::cout << k << ": " << value.as<std::string>() << std::endl;
      break;
    }
    case sol::type::number: {
      auto v = value.as<double>();
      std::cout << k << ": " << v << std::endl;
      break;
    }

    case sol::type::table: {
      auto v = value.as<sol::table>();
      std::cout << k << " : {" << std::endl;
      printTable(v);
      std::cout << "}" << std::endl;
      break;
    }
    default: { std::cout << "hit the default case!" << std::endl; }
    }
    // inspect key/value, manipulate as you please
  }
}

GameState::GameState(gameDataRef data) {
  this->_data = data;
  this->script.set_function("say", [](std::string text) {
    std::cout << "Player: " << text << std::endl;
  });
  this->script.script_file("scripts/player.lua");
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