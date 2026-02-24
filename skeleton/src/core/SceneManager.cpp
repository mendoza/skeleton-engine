#include <skeleton/core/Logger.hpp>
#include <skeleton/core/SceneManager.hpp>

namespace skeleton::core {

void SceneManager::add_scene(SceneRef scene, bool is_replacing) {
  if (is_replacing && !scenes.empty()) {
    scenes.top()->on_destroy();
    scenes.pop();
  }
  scenes.push(std::move(scene));
  scenes.top()->on_init();
  Logger::info("Scene pushed: " + scenes.top()->get_name());
}

void SceneManager::remove_scene() {
  if (scenes.empty())
    return;
  scenes.top()->on_destroy();
  scenes.pop();
  if (!scenes.empty())
    scenes.top()->on_resume();
}

Scene *SceneManager::get_active_scene() {
  if (scenes.empty())
    return nullptr;
  return scenes.top().get();
}

} // namespace skeleton::core
