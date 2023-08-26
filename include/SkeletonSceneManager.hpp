#ifndef SKELETON_SCENE_MANAGER_HPP
#define SKELETON_SCENE_MANAGER_HPP

#include <SceneManager.hpp>

namespace skeleton {
class SkeletonSceneManager : public SceneManager {
  public:
	SkeletonSceneManager() {}
	~SkeletonSceneManager() {
		logger->log("Started cleaning the  scene manager stack");
		while (!this->scenes.empty()) {
			std::shared_ptr ptr = std::move(this->scenes.top());
			this->scenes.pop();
		}
		logger->log("Finished cleaning the  scene manager stack");
	}

	void add_scene(SceneRef new_scene, bool is_replacing = true);
	void remove_scene();
	Scene *get_active_scene();

  protected:
	std::stack<SceneRef> scenes;
};
}; // namespace skeleton

#endif