#ifndef SKELETON_SCENE_HPP
#define SKELETON_SCENE_HPP

#include <SDL.h>
#include <memory>
#include <skeleton/core/Logger.hpp>
#include <skeleton/graphics/Renderer.hpp>
#include <skeleton/nodes/DrawableNode.hpp>
#include <skeleton/nodes/Node2D.hpp>
#include <sol/sol.hpp>

namespace skeleton::core {
class Scene : public skeleton::nodes::Node2D {
protected:
  bool debug_mode;
  skeleton::core::Logger *logger = skeleton::core::Logger::get_instance();

public:
  Scene() : Node2D() { name = "Scene"; }
  Scene(std::string name) : Node2D() { name = name; }

  virtual ~Scene() {}

  // NOTE: these should be implemented by the user
  virtual void handle_init() = 0;
  virtual void handle_input(SDL_Event &event) = 0;
  virtual void handle_update(double dt) = 0;
  virtual void handle_fixed_update(double dt) = 0;
  virtual void handle_draw() = 0;
  virtual void handle_destroy() = 0;
  virtual void draw_debug_window() = 0;

  virtual void draw() {
    skeleton::graphics::Renderer::get_instance().begin();
    handle_draw();
    draw_debug_window();
    for (auto child : this->children) {
      if (auto drawableChild =
              dynamic_cast<skeleton::nodes::DrawableNode *>(child)) {
        drawableChild->draw();
      }
    }
    skeleton::graphics::Renderer::get_instance().end();
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
}; // namespace skeleton::core

#endif
