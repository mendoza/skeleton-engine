#ifndef SKELETON_SCENE_MACHINE_HPP
#define SKELETON_SCENE_MACHINE_HPP

#include <Scene.hpp>
#include <memory>
#include <stack>

namespace skeleton {
class SceneManager {

  public:
	SceneManager() {}
	~SceneManager() {}

	void add_scene(SceneRef new_scene, bool is_replacing = true);
	void remove_scene();
	void process_scene_changes();
	Scene *get_active_scene();

  private:
	std::stack<SceneRef> scenes;
	SceneRef latest_scene;
	bool is_removing = false;
	bool is_adding = false;
	bool is_replacing = false;
};
}; // namespace skeleton

#endif