#include <GameData.hpp>

namespace skeleton {

GameData::GameData() {}

GameData::~GameData() {}

void GameData::setStateMachine(StateMachine *new_ptr) {
	this->Machine = new_ptr;
}

void GameData::logEngine() {
	ImGui::Text("FPS: %.0f", this->FPS);
	ImGui::Text("Resolution: %dx%d", this->Window.getSize().x,
				this->Window.getSize().y);
}
} // namespace skeleton
