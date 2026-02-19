#include "FarmScene.hpp"
#include <skeleton/core/Logger.hpp>
#include <skeleton/graphics/Renderer.hpp>
#include <skeleton/input/InputManager.hpp>
#include <skeleton/math/types.hpp>
#include <skeleton/scripting/script_component.hpp>

struct Position {
  skeleton::Vec2 pos;
};

struct Player {};

FarmScene::FarmScene(std::string name) : Scene(std::move(name)) {}

void FarmScene::on_init() {
  using namespace skeleton::scripting;
  using namespace skeleton::input;

  lua.open_libraries(sol::lib::base, sol::lib::math);
  lua.new_usertype<skeleton::Vec2>("Vec2", "x", &skeleton::Vec2::x, "y",
                                   &skeleton::Vec2::y);
  lua.new_usertype<Position>("__Position", "pos", &Position::pos);
  lua.new_usertype<Player>("__Player");

  bind_entity_handle(lua);
  bind_component<Position>(lua, "Position");
  bind_component<Player>(lua, "Player");
  bind_input(lua);

  auto &r = skeleton::graphics::Renderer::get_instance();
  auto player = registry.create();
  registry.emplace<Position>(player,
                             skeleton::Vec2{r.get_window_width() / 2.0f,
                                            r.get_window_height() / 2.0f});
  registry.emplace<Player>(player);

  ScriptComponent sc;
  sc.path = "assets/scripts/player.lua";
  sc.env = sol::environment(lua, sol::create, lua.globals());
  registry.emplace<ScriptComponent>(player, std::move(sc));
}

void FarmScene::on_input(SDL_Event &) {}
void FarmScene::on_update(double) {}

void FarmScene::on_fixed_update(double dt) {
  using namespace skeleton::scripting;

  auto view = registry.view<ScriptComponent>();
  for (auto [e, sc] : view.each()) {
    if (!sc.initialized) {
      auto result =
          lua.safe_script_file(sc.path, sc.env, sol::script_pass_on_error);
      if (!result.valid()) {
        sol::error err = result;
        skeleton::core::Logger::error(err.what());
      } else {
        sol::protected_function on_init = sc.env["on_init"];
        if (on_init.valid()) {
          EntityHandle handle{&registry, e};
          auto r = on_init(handle);
          if (!r.valid()) {
            sol::error err = r;
            skeleton::core::Logger::error(err.what());
          }
        }
      }
      sc.initialized = true;
    }

    sol::protected_function on_update = sc.env["on_update"];
    if (on_update.valid()) {
      EntityHandle handle{&registry, e};
      auto result = on_update(handle, (float)dt);
      if (!result.valid()) {
        sol::error err = result;
        skeleton::core::Logger::error(err.what());
      }
    }
  }
}

void FarmScene::on_draw() {
  auto &r = skeleton::graphics::Renderer::get_instance();

  auto view = registry.view<Position, Player>();
  for (auto [e, pos] : view.each()) {
    skeleton::Rect rect = {pos.pos.x - 16, pos.pos.y - 16, 32, 32};
    r.draw_rect(rect, {100, 200, 100, 255});
  }
}

void FarmScene::on_destroy() { registry.clear(); }
void FarmScene::on_debug_ui() {
  skeleton::input::InputManager::get_instance().debug_ui();
}
