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
	bool DebugMode;
	float FPS;
	int Width;
	int Height;
	int Limit;
	bool VSync;

	void setMetaData(int width, int height, int Limit, bool vsync) {
		this->Width = width;
		this->Height = height;
		this->Limit = Limit;
		this->VSync = vsync;
	}

	void logEngine() {
		ImGui::Text("FPS: %.0f", this->FPS);
		if (this->Limit != 0)
			ImGui::Text("FPS Limit: %.d", this->Limit);
		ImGui::Text("VSync: %s", this->VSync ? "on" : "off");
		ImGui::Checkbox("test", &this->VSync);
		std::cout << &this->VSync << std::endl;
		this->VSync = true;
		ImGui::Text("Resolution: %dx%d", this->Width, this->Height);
	}
};

typedef std::shared_ptr<GameData> GameDataRef;
class Engine {
  public:
	Engine(bool DebugMode = false);
	void buildWindow(int Width, int Height, std::string Title,
					 std::string IconFile, int Limit = 60, bool VSync = false);

  private:
	sf::Clock Clock;
	const float dt = 1.f / 60.f;
	GameDataRef Data = std::make_shared<GameData>();
	void run();
};
}; // namespace skeleton
