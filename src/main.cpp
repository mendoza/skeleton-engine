#include <Game.hpp>
#include <sol.hpp>
#include <string>
#include <vector>
int main() {
  sol::state script;
  script.script_file("scripts/game.lua");
  sol::table game = script["game"];
  std::string title = game["title"];
  int width = game["width"];
  int height = game["height"];
  int limit = game["fpsLimit"];
  Skeleton::Game(width, height, title, limit);
  return 0;
}