#ifndef SCENE_MANAGER_SERVICE_HPP
#define SCENE_MANAGER_SERVICE_HPP

#include "Scene.hpp"
#include "Service.hpp"
#include <memory>
#include <stack>

namespace skeleton {
class SceneManager : public Service {

  public:
	SceneManager() {}
	~SceneManager() {}

	virtual void add_scene(SceneRef new_scene, bool is_replacing = true) = 0;
	virtual void remove_scene() = 0;
	virtual Scene *get_active_scene() = 0;
};
}; // namespace skeleton

#endif