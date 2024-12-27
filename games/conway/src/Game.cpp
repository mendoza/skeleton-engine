#include "SimulationScene.hpp"
#include <skeleton/Core/Engine.hpp>
#include <skeleton/Core/SceneManager.hpp>
#include <sol/sol.hpp>

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
  skeleton::SceneManager::get_instance().add_scene(
      std::make_unique<SimulationScene>("GOL"), false);
  engine.run();
  return 0;
}
