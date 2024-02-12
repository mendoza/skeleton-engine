#ifndef SKELETON_SCENE_MANAGER_HPP
#define SKELETON_SCENE_MANAGER_HPP

#include "SceneManager.hpp"
#include <stack>


namespace skeleton {
class SkeletonSceneManager : public SceneManager {
  public:
	SkeletonSceneManager();
	~SkeletonSceneManager();

	void add_scene(SceneRef new_scene, bool is_replacing) override;
	void remove_scene() override;
	Scene *get_active_scene() override;

  protected:
	std::stack<SceneRef> scenes;
};
}; // namespace skeleton

#endif
