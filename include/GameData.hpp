#ifdef SKELETON_GAME_DATA_HPP
#error this header is already defined
#endif

#ifndef SKELETON_GAME_DATA_HPP
#define SKELETON_GAME_DATA_HPP

#include <AssetManager.hpp>
#include <InputManager.hpp>
#include <Logger.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace skeleton {
	class StateMachine;
class GameData {
  public:
	GameData();
	~GameData();
	sf::RenderWindow Window;
	StateMachine Machine;
	AssetManager Assets;
	InputManager Input;
	float FPS;
	bool DebugMode;

	void logEngine();
};

typedef std::shared_ptr<GameData> GameDataRef;

} // namespace skeleton

#endif