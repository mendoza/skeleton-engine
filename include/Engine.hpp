#ifndef SKELETON_ENGINE_HPP
#define SKELETON_ENGINE_HPP

#include <GameData.hpp>
#include <SFML/System/Clock.hpp>
#include <StateMachine.hpp>

namespace skeleton {

class Engine {
  public:
	Engine(bool debug_mode = false);
	void build_window(sf::Vector2u resolution, std::string Title,
					 std::string IconFile, bool fullscreen);

  private:
	sf::Clock clock;
	const float dt = 1.f / 60.f;
	GameDataRef data = std::make_shared<GameData>();
	void run();
};
}; // namespace skeleton

#endif