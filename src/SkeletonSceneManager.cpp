#include "SkeletonSceneManager.hpp"

namespace skeleton {
void SkeletonSceneManager::add_scene(SceneRef new_state, bool is_replacing) {
	if (is_replacing && !this->scenes.empty()) {
		this->scenes.top()->destroy();
		this->scenes.pop();
	}

	this->scenes.push(std::move(new_state));
	this->scenes.top()->init();
}

void SkeletonSceneManager::remove_scene() {
	if (!this->scenes.empty()) {
		this->scenes.top()->destroy();
		this->scenes.pop();
		this->scenes.top()->resume();
	}
}

Scene *SkeletonSceneManager::get_active_scene() {
	return this->scenes.top().get();
}
}; // namespace skeleton