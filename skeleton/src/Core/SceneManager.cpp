#include <skeleton/core/SceneManager.hpp>

namespace skeleton::core {

SceneManager::SceneManager() = default;

SceneManager::~SceneManager() {
  logger->info("Cleaning the  scene manager stack");
  while (!this->scenes.empty()) {
    skeleton::core::SceneRef scene = std::move(this->scenes.top());
    scene->destroy();
    this->scenes.pop();
  }
  logger->info("Finished cleaning the  scene manager stack");
}

void SceneManager::add_scene(SceneRef new_state, bool is_replacing) {
  if (is_replacing && !this->scenes.empty()) {
    this->scenes.top()->destroy();
    this->scenes.pop();
  }

  this->scenes.push(std::move(new_state));
  this->scenes.top()->init();
}

void SceneManager::remove_scene() {
  if (!this->scenes.empty()) {
    this->scenes.top()->destroy();
    this->scenes.pop();
    if (!this->scenes.empty()) {
      this->scenes.top()->init();
    }
  }
}

Scene *SceneManager::get_active_scene() {
  if (this->scenes.empty()) {
    return nullptr;
  }
  return this->scenes.top().get();
}
}; // namespace skeleton::core
