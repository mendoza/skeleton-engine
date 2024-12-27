#ifndef SKELETON_SCENE_MANAGER_HPP
#define SKELETON_SCENE_MANAGER_HPP

#include "ISceneManager.hpp"
#include <stack>

namespace skeleton {
class SceneManager : public skeleton::ISceneManager {
public:
  static SceneManager &get_instance() {
    static SceneManager instance;
    return instance;
  }

  SceneManager(const SceneManager &) = delete;
  SceneManager &operator=(const SceneManager &) = delete;

  void add_scene(SceneRef new_scene, bool is_replacing) override;
  void remove_scene() override;
  Scene *get_active_scene() override;

private:
  SceneManager();
  ~SceneManager();

  std::stack<SceneRef> scenes;
};
}; // namespace skeleton

#endif
