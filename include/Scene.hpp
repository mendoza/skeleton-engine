#ifndef SKELETON_SCENE_HPP
#define SKELETON_SCENE_HPP

#include "AssetManager.hpp"
#include "Logger.hpp"
#include "Node.hpp"
#include "ScriptManager.hpp"
#include "ServiceLocator.hpp"
#include "Utils.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <sol/sol.hpp>

namespace skeleton {
class Scene : public Node {
protected:
  bool debug_mode;
  skeleton::Logger *logger = skeleton::Logger::get_instance();
  skeleton::AssetManager *asset_manager;
  skeleton::ScriptManager *script_manager;

public:
  Scene(std::string tag) {
    asset_manager = new AssetManager();
    script_manager = new ScriptManager();
    this->tag = tag;
  }
  virtual ~Scene() {
    delete asset_manager;
    delete script_manager;
  }

  virtual void initialize() = 0;
  virtual void handle_input(SDL_Event &event) = 0;
  virtual void update(float dt) {
    for (auto child : children) {
      child->update(dt);
    }
  }
  virtual void draw() override {
    skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->begin();
    draw_debug_window();
    for (auto child : children) {
      child->draw();
    }
    skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->end();
  }
  // virtual void fixed_update(float dt) = 0;
  virtual void draw_debug_window() = 0;
  virtual void destroy() = 0;
};
typedef std::unique_ptr<Scene> SceneRef;

}; // namespace skeleton

#endif
