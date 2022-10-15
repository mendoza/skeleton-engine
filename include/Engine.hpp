#ifndef SKELETON_ENGINE_HPP
#define SKELETON_ENGINE_HPP

#include <GameData.hpp>
#include <SFML/System/Clock.hpp>
#include <StateMachine.hpp>

namespace skeleton {

class Engine {
  public:
	Engine(bool DebugMode = false);
	void buildWindow(int Width, int Height, std::string Title,
					 std::string IconFile);

  private:
	sf::Clock Clock;
	const float dt = 1.f / 60.f;
	GameDataRef Data = std::make_shared<GameData>();
	void run();
};
}; // namespace skeleton

#endif