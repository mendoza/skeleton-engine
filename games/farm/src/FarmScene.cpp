#include "FarmScene.hpp"
#include <imgui.h>
#include <skeleton/audio/AudioManager.hpp>
#include <skeleton/core/Logger.hpp>
#include <skeleton/debug/widget_registry.hpp>
#include <skeleton/graphics/Renderer.hpp>
#include <skeleton/input/InputManager.hpp>
#include <skeleton/math/types.hpp>
#include <skeleton/scripting/script_component.hpp>

struct Position {
  skeleton::Vec2 pos;
};

struct Player {};

static void register_debug_widgets() {
  static bool registered = false;
  if (registered) return;
  registered = true;

  skeleton::debug::register_widget<Position>("Position", [](Position &p) {
    ImGui::DragFloat2("pos", &p.pos.x, 1.0f);
  });
  skeleton::debug::register_widget<Player>("Player", [](Player &) {
    ImGui::TextDisabled("(tag)");
  });
}

FarmScene::FarmScene(std::string name) : Scene(std::move(name)) {
  register_debug_widgets();
}

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
  camera.zoom = 4.0f;

  auto player = registry.create();
  registry.emplace<Position>(player,
                             skeleton::Vec2{r.get_window_width() / 2.0f,
                                            r.get_window_height() / 2.0f});
  registry.emplace<Player>(player);
  skeleton::graphics::AnimationPlayer anim;
  anim.load("assets/farm rpg assets/Character/idle.lua");
  anim.merge("assets/farm rpg assets/Character/walk.lua");
  registry.emplace<skeleton::graphics::AnimationPlayer>(player, std::move(anim));

  ScriptComponent sc;
  sc.path = "assets/scripts/player.lua";
  sc.env = sol::environment(lua, sol::create, lua.globals());
  registry.emplace<ScriptComponent>(player, std::move(sc));
}

void FarmScene::on_input(SDL_Event &) {}
void FarmScene::on_update(double dt) {
  auto &input = skeleton::input::InputManager::get_instance();
  bool moving = false;

  if      (input.held("move_right")) { last_dir_ = "right"; moving = true; }
  else if (input.held("move_left"))  { last_dir_ = "left";  moving = true; }
  else if (input.held("move_down"))  { last_dir_ = "down";  moving = true; }
  else if (input.held("move_up"))    { last_dir_ = "up";    moving = true; }

  for (auto [e, pos] : registry.view<Player, Position>().each())
    camera.position = pos.pos;

  auto &audio = skeleton::audio::AudioManager::get_instance();
  if (moving && walk_channel_ < 0)
    walk_channel_ = audio.play("walking", -1);
  else if (!moving && walk_channel_ >= 0) {
    audio.stop_channel(walk_channel_);
    walk_channel_ = -1;
  }

  auto view = registry.view<Player, skeleton::graphics::AnimationPlayer>();
  for (auto [e, anim] : view.each()) {
    anim.play((moving ? "walk_" : "idle_") + last_dir_);
    anim.update((float)dt);
  }
}

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
  r.set_camera(camera);

  auto view = registry.view<Position, skeleton::graphics::AnimationPlayer>();
  for (auto [e, pos, anim] : view.each()) {
    skeleton::Rect src = anim.current_rect();
    skeleton::Rect dst = {pos.pos.x - 16, pos.pos.y - 16,
                          (float)anim.frame_w(), (float)anim.frame_h()};
    r.draw_texture(anim.current_texture(), &src, &dst, 0.0f, anim.current_flip());
  }
  r.reset_camera();
}

void FarmScene::on_destroy() { registry.clear(); }
