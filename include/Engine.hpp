#pragma once
#include <AnimationManager.hpp>
#include <AssetManager.hpp>
#include <InputManager.hpp>
#include <Logger.hpp>
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

namespace skeleton {

struct GameData {
	StateMachine Machine;
	sf::RenderWindow Window;
	AssetManager Assets;
	InputManager Input;
	float FPS;
	bool DebugMode;

	void logEngine() {
		ImGui::Text("FPS: %.0f", this->FPS);
		ImGui::Text("Resolution: %dx%d", this->Window.getSize().x,
					this->Window.getSize().y);
	}
};

typedef std::shared_ptr<GameData> GameDataRef;
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
