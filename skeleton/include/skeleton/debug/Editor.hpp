#pragma once
#include <SDL.h>
#include <entt/entt.hpp>
#include <skeleton/core/Scene.hpp>

namespace skeleton::debug {

class Editor {
public:
  void draw(SDL_Texture *scene_tex, skeleton::core::Scene *scene);

private:
  entt::entity selected_ = entt::null;

  void draw_settings(skeleton::core::Scene *scene);
  void draw_scene(SDL_Texture *scene_tex);
  void draw_inspector(skeleton::core::Scene *scene);
};

} // namespace skeleton::debug
