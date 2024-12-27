#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include "skeleton/core/Scene.hpp"
#include <SDL.h>
#include <imgui.h>
#include <sol/sol.hpp>
#include <string>
class SimulationScene : public skeleton::core::Scene {
public:
  SimulationScene(std::string name);
  ~SimulationScene() override;
  void handle_init() override;
  void handle_input(SDL_Event &event) override;
  void handle_update(double dt) override;
  void handle_fixed_update(double dt) override;
  void handle_draw() override;
  void handle_destroy() override;

  void draw_debug_window() override;
  std::string get_particle_system_name();

private:
  sol::function script_on_update;
  sol::function script_handle_input;
  // conway's game of life
};

#endif
