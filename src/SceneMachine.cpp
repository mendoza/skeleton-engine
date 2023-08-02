#include <SceneManager.hpp>

namespace skeleton {
void SceneManager::add_scene(std::unique_ptr<Scene> newState,
							 bool isReplacing) {
	this->is_adding = true;
	this->is_replacing = isReplacing;
	this->latest_scene = std::move(newState);
}

void SceneManager::remove_scene() { this->is_removing = true; }

void SceneManager::process_scene_changes() {
	if (this->is_removing && !this->scenes.empty()) {
		this->scenes.pop();
		if (!this->scenes.empty()) {
			this->scenes.top()->resume();
		}
		this->is_removing = false;
	}

	if (this->is_adding) {
		if (!this->scenes.empty()) {
			if (this->is_replacing) {
				this->scenes.pop();
			} else {
				this->scenes.top();
			}
		}

		this->scenes.push(std::move(this->latest_scene));
		this->scenes.top()->init();
		this->is_adding = false;
	}
}

std::unique_ptr<Scene> &SceneManager::get_active_scene() {
	return this->scenes.top();
}
}; // namespace skeleton