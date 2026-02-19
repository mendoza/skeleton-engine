#include "BoidsScene.hpp"
#include <skeleton/core/Engine.hpp>
#include <sol/sol.hpp>

int main(int, char **) {
  sol::state lua;
  lua.script_file("assets/scripts/config.lua");
  sol::table config = lua["config"];

  std::string title = config["title"];
  std::string icon = config["icon"];
  unsigned int w = config["resolution"]["width"];
  unsigned int h = config["resolution"]["height"];
  bool debug_mode = config["debug_mode"];
  bool fullscreen = config["fullscreen"];

  skeleton::core::Engine engine(debug_mode);
  engine.build_window(w, h, title, icon, fullscreen);
  engine.add_scene(std::make_unique<BoidsScene>("Boids"));
  engine.run();

  return 0;
}
