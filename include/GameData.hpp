#ifdef SKELETON_GAME_DATA_HPP
#error this header is already defined
#endif

#ifndef SKELETON_GAME_DATA_HPP
#define SKELETON_GAME_DATA_HPP

#include <AssetManager.hpp>
#include <InputManager.hpp>
#include <Logger.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <StateMachine.hpp>

namespace skeleton {
class GameData {
  public:
	GameData();
	~GameData();
	StateMachine Machine;
	sf::RenderWindow Window;
	AssetManager Assets;
	InputManager Input;
	float FPS;
	bool DebugMode;

	void logEngine();
};

typedef std::shared_ptr<GameData> GameDataRef;

} // namespace skeleton

#endif