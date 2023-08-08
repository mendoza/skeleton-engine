#ifndef SKELETON_SCENE_MANAGER_HPP
#define SKELETON_SCENE_MANAGER_HPP

#include <SceneManager.hpp>

namespace skeleton {
class SkeletonSceneManager : public SceneManager {

  public:
	SkeletonSceneManager() {}
	~SkeletonSceneManager() {
		while (!this->scenes.empty()) {
			std::unique_ptr ptr = std::move(this->scenes.top());
			this->scenes.pop();
		}
	}

	void add_scene(SceneRef new_scene, bool is_replacing = true);
	void remove_scene();
	void process_scene_changes();
	Scene *get_active_scene();
};
}; // namespace skeleton

#endif