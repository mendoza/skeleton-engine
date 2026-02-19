#pragma once
#include <SDL.h>
#include <skeleton/core/Scene.hpp>
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
  void on_debug_ui() override;

private:
  sol::state lua;
};
