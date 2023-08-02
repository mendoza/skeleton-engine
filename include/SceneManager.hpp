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

	void add_scene(std::unique_ptr<Scene> new_scene, bool is_replacing = true);
	void remove_scene();
	void process_scene_changes();
	std::unique_ptr<Scene> &get_active_scene();

  private:
	std::stack<std::unique_ptr<Scene>> scenes;
	std::unique_ptr<Scene> latest_scene;
	bool is_removing;
	bool is_adding;
	bool is_replacing;
};
}; // namespace skeleton

#endif