#pragma once
#include <SDL.h>
#include <skeleton/core/Scene.hpp>
#include <skeleton/graphics/AnimationPlayer.hpp>
#include <skeleton/math/types.hpp>
#include <sol/sol.hpp>

class FarmScene : public skeleton::core::Scene {
public:
  explicit FarmScene(std::string name);
  ~FarmScene() override = default;

  void on_init() override;
  void on_input(SDL_Event &event) override;
  void on_update(double dt) override;
  void on_fixed_update(double dt) override;
  void on_draw() override;
  void on_destroy() override;

private:
  sol::state lua;
  std::string last_dir_ = "down";
  int walk_channel_ = -1;
  skeleton::Camera2D camera;
};
