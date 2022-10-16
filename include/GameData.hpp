#ifndef SKELETON_GAME_DATA_HPP
#define SKELETON_GAME_DATA_HPP

#include <AssetManager.hpp>
#include <InputManager.hpp>
#include <Logger.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui.h>
#include <memory>

namespace skeleton {
class StateMachine;
class GameData {
  public:
	GameData();
	~GameData();
	sf::RenderWindow render_window;
	StateMachine *state_machine;
	AssetManager asset_manager;
	InputManager input_manager;
	float fps;
	bool debug_mode;
	void set_state_machine(StateMachine *);
	void log_engine();
};

typedef std::shared_ptr<GameData> GameDataRef;

} // namespace skeleton

#endif