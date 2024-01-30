#include "SkeletonSceneManager.hpp"

namespace skeleton {

SkeletonSceneManager::SkeletonSceneManager() = default;

SkeletonSceneManager::~SkeletonSceneManager() {
	logger->log("Started cleaning the  scene manager stack");
	while (!this->scenes.empty()){
		this->scenes.pop();
		logger->log("Delete one scene");
	}
	logger->log("Finished cleaning the  scene manager stack");
}

void SkeletonSceneManager::add_scene(SceneRef new_state, bool is_replacing) {
	if (is_replacing && !this->scenes.empty()) {
		this->scenes.top()->destroy();
		this->scenes.pop();
	}

	this->scenes.push(std::move(new_state));
	this->scenes.top()->initialize();
}

void SkeletonSceneManager::remove_scene() {
	if (!this->scenes.empty()) {
		this->scenes.top()->destroy();
		this->scenes.pop();
		this->scenes.top()->initialize();
	}
}

Scene *SkeletonSceneManager::get_active_scene() {
	return this->scenes.top().get();
}
}; // namespace skeleton