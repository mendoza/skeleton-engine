#ifndef SKELETON_GAME_DATA_HPP
#define SKELETON_GAME_DATA_HPP

#include <AssetManager.hpp>
#include <Logger.hpp>
#include <SDL2/SDL.h>
#include <memory>
namespace skeleton {
class SceneManager;
class GameData {
  public:
	GameData();
	~GameData();
	SceneManager *state_machine;
	AssetManager asset_manager;
	bool is_running;
	float fps;
	bool debug_mode;
	void set_state_machine(SceneManager *);
	void log_engine();
};

typedef std::shared_ptr<GameData> GameDataRef;

} // namespace skeleton

#endif