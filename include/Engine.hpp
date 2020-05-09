#pragma once
#include <AssetManager.hpp>
#include <InputManager.hpp>
#include <OpenECS.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <State.hpp>
#include <StateMachine.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <sol.hpp>
#include <string>
#include <vector>

namespace Skeleton {
struct GameData {
	StateMachine Machine;
	sf::RenderWindow Window;
	AssetManager Assets;
	InputManager Input;
	bool DebugMode;
};

typedef std::shared_ptr<GameData> GameDataRef;
class Engine {
  public:
	Engine(int Width, int Height, std::string Title, std::string IconFile,
		   int Limit = 60, bool VSync = false, bool DebugMode = false);

  private:
	sf::Clock Clock;
	const float dt = 1.0f / 6.0f;
	GameDataRef Data = std::make_shared<GameData>();
	void run();
};
}; // namespace Skeleton
