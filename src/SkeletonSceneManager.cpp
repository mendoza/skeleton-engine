#include "SkeletonSceneManager.hpp"

namespace skeleton {

SkeletonSceneManager::SkeletonSceneManager() = default;

SkeletonSceneManager::~SkeletonSceneManager() {
	logger->log("Cleaning the  scene manager stack");
	while (!this->scenes.empty()){
		skeleton::SceneRef scene = std::move(this->scenes.top());
		scene->destroy();
		std::string scene_name = scene->get_tag();
		this->scenes.pop();
		if (scene_name.empty()){
			logger->log("Delete one scene");
		} else {
			logger->log("Delete one scene: " + scene_name);
		}
	}
	logger->log("Finished cleaning the  scene manager stack");
}

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
		if (!this->scenes.empty()){
			this->scenes.top()->init();
		}
	}
}

Scene *SkeletonSceneManager::get_active_scene() {
	if (this->scenes.empty()) {
		return nullptr;
	}
	return this->scenes.top().get();
}
}; // namespace skeleton
