#pragma once
#include <AssetManager.hpp>
#include <ECS.hpp>
#include <InputManager.hpp>
#include <SFML/Graphics.hpp>
#include <StateMachine.hpp>
#include <memory>
#include <string>

namespace Skeleton {
using namespace ecs;
struct gameData {
  StateMachine machine;
  sf::RenderWindow window;
  AssetManager assets;
  InputManager input;
  sf::Clock _clock;
  EntityManager entities;
  SystemManager systems = SystemManager(this->entities);
  ;
};

typedef std::shared_ptr<gameData> gameDataRef;
class Game {
public:
  Game(int width, int height, std::string title);

private:
  sf::Clock _clock;
  const float dt = 1.0f / 6.0f;
  gameDataRef _data = std::make_shared<gameData>();
  void run();
};
} // namespace Skeleton