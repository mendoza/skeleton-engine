#include <SkeletonSceneManager.hpp>

namespace skeleton {
void SkeletonSceneManager::add_scene(SceneRef newState, bool isReplacing) {
	this->is_adding = true;
	this->is_replacing = isReplacing;
	this->latest_scene = std::move(newState);
}

void SkeletonSceneManager::remove_scene() { this->is_removing = true; }

void SkeletonSceneManager::process_scene_changes() {
	if (this->is_removing && !this->scenes.empty()) {
		this->scenes.top().get()->destroy();
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

Scene *SkeletonSceneManager::get_active_scene() {
	return this->scenes.top().get();
}
}; // namespace skeleton