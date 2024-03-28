#include "Engine.hpp"
#include "TestScene.hpp"
#include <lua.hpp>
#include <sol/sol.hpp>
skeleton::Logger *skeleton::Logger::instance = 0;

int main(int argv, char **args) {
  sol::state L;
  L.script_file("assets/scripts/config.lua");
  sol::table config = L["config"];
  std::string title = config["title"];
  std::string icon = config["icon"];
  sol::table initial_resolution = config["resolution"];
  unsigned int Width = initial_resolution["width"];
  unsigned int Height = initial_resolution["height"];
  bool debug_mode = config["debug_mode"];
  bool fullscreen = config["fullscreen"];
  skeleton::Engine engine(debug_mode);
  engine.build_window(Width, Height, title, icon, fullscreen);
  engine.add_scene(std::make_unique<TestScene>("test scene"));
  engine.run();
  return 0;
}
