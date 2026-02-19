#pragma once
#include <SDL.h>
#include <skeleton/core/Scene.hpp>
#include <skeleton/math/types.hpp>
#include <sol/sol.hpp>

class BoidsScene : public skeleton::core::Scene {
public:
  explicit BoidsScene(std::string name);
  ~BoidsScene() override = default;

  void on_init() override;
  void on_input(SDL_Event &event) override;
  void on_update(double dt) override;
  void on_fixed_update(double dt) override;
  void on_draw() override;
  void on_destroy() override;
  void on_debug_ui() override;

private:
  sol::state lua;

  skeleton::Camera2D camera;
  bool panning      = false;
  int  last_mouse_x = 0;
  int  last_mouse_y = 0;

  float world_w = 3840.0f;
  float world_h = 2160.0f;

  float perception = 60.0f;
  float max_speed  = 120.0f;
  float max_force  = 200.0f;
  float sep_weight = 1.5f;
  float ali_weight = 1.0f;
  float coh_weight = 1.0f;
};
