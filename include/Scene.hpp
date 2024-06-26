#ifndef SKELETON_SCENE_HPP
#define SKELETON_SCENE_HPP

#include "DrawableNode.hpp"
#include "Logger.hpp"
#include "Node2D.hpp"
#include "ScriptManager.hpp"
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
  Scene(std::string tag) : Node2D(tag) {
    script_manager = new ScriptManager();
    name = "Scene";
  }

  virtual ~Scene() { delete script_manager; }

  // NOTE: these should be implemented by the user
  virtual void handle_init() = 0;
  virtual void handle_input(SDL_Event &event) = 0;
  virtual void handle_update(double dt) = 0;
  virtual void handle_fixed_update(double dt) = 0;
  virtual void handle_draw() = 0;
  virtual void handle_destroy() = 0;
  virtual void draw_debug_window() = 0;

  virtual void draw() {
    skeleton::Renderer::get_instance().begin();
    handle_draw();
    draw_debug_window();
    for (auto child : this->children) {
      if (auto drawableChild = dynamic_cast<DrawableNode *>(child)) {
        drawableChild->draw();
      }
    }
    skeleton::Renderer::get_instance().end();
  }

  virtual void init() {
    handle_init();
    for (auto child : this->children) {
      if (dynamic_cast<Scene *>(child)) {
        dynamic_cast<Scene *>(child)->init();
      }
    }
  }

  virtual void destroy() {
    handle_destroy();
    for (auto child : this->children) {
      if (dynamic_cast<Scene *>(child)) {
        dynamic_cast<Scene *>(child)->destroy();
      }
    }
  }
};
typedef std::unique_ptr<Scene> SceneRef;
}; // namespace skeleton

#endif
