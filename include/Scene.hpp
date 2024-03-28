#ifndef SKELETON_SCENE_HPP
#define SKELETON_SCENE_HPP

#include "Logger.hpp"
#include "Node.hpp"
#include "Nodes.hpp"
#include "ScriptManager.hpp"
#include "ServiceLocator.hpp"
#include <SDL.h>
#include <memory>
#include <sol/sol.hpp>

namespace skeleton {
class Scene : public Node2D {
protected:
  bool debug_mode;
  skeleton::Logger *logger = skeleton::Logger::get_instance();
  skeleton::ScriptManager *script_manager;

public:
  Scene(std::string tag) : Node2D(tag) { script_manager = new ScriptManager(); }

  virtual ~Scene() { delete script_manager; }

  virtual void initialize() = 0;
  virtual void handle_input(SDL_Event &event) = 0;

  virtual void draw() {
    skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->begin();
    draw_debug_window();
    for (auto child : this->children) {
      if (dynamic_cast<DrawableNode *>(child)) {
        dynamic_cast<DrawableNode *>(child)->draw();
      }
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
