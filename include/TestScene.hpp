#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include "Scene.hpp"
#include <SDL.h>
#include <imgui.h>
#include <sol/sol.hpp>
#include <string>
class TestScene : public skeleton::Scene {
public:
  TestScene(std::string tag);
  ~TestScene() override;
  void handle_init() override;
  void handle_input(SDL_Event &event) override;
  void handle_update(double dt) override;
  // void fixed_update(float dt) override;
  void handle_draw() override;
  void handle_destroy() override;

  void draw_debug_window() override;
  void setupLuaState();
  std::string get_particle_system_name();

private:
  SDL_Surface *background;
  sol::function script_on_update;
  sol::function script_handle_input;
  int particle_system_count = 0;
};

#endif
