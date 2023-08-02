#include <GameData.hpp>

namespace skeleton {

GameData::GameData() {}

GameData::~GameData() {}

void GameData::set_state_machine(SceneManager *new_ptr) {
	this->state_machine = new_ptr;
}

void GameData::log_engine() {
	// ImGui::Text("FPS: %.0f", this->fps);
	// ImGui::Text("Resolution: %dx%d", this->render_window.getSize().x,
	// 			this->render_window.getSize().y);
}
} // namespace skeleton
