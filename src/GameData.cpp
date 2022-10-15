#include <GameData.hpp>

namespace skeleton {

GameData::GameData() {}

GameData::~GameData() {}

void GameData::logEngine() {
	ImGui::Text("FPS: %.0f", this->FPS);
	ImGui::Text("Resolution: %dx%d", this->Window.getSize().x,
				this->Window.getSize().y);
}
} // namespace skeleton
