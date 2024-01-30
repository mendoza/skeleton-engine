#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include "Components.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Utils.hpp"
#include <SDL2/SDL.h>
#include <imgui.h>
#include <sol/sol.hpp>
#include <string>
class TestScene : public skeleton::Scene {
public:
  TestScene(std::string tag);
  ~TestScene() override;
  void initialize() override;
  void handle_input(SDL_Event &event) override;
  // void fixed_update(float dt) override;
  void draw_debug_window() override;
  void destroy() override;
  void setupLuaState();

private:
  SDL_Surface *background;
  sol::function script_on_update;
  sol::function script_handle_input;
};

#endif
