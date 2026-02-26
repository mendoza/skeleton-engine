#include "FarmScene.hpp"
#include <imgui.h>
#include <skeleton/audio/AudioManager.hpp>
#include <skeleton/debug/widget_registry.hpp>
#include <skeleton/graphics/AnimationPlayer.hpp>
#include <skeleton/graphics/Renderer.hpp>
#include <skeleton/input/InputManager.hpp>
#include <skeleton/scripting/script_component.hpp>

struct Position {
  skeleton::Vec2 pos;
};

struct Player {};
struct Cow {};

static void register_debug_widgets() {
  static bool registered = false;
  if (registered)
    return;
  registered = true;

  skeleton::debug::register_widget<Position>("Position", [](Position &p) {
    ImGui::DragFloat2("pos", &p.pos.x, 1.0f);
  });
  skeleton::debug::register_widget<Player>(
      "Player", [](Player &) { ImGui::TextDisabled("(tag)"); });
  skeleton::debug::register_widget<Cow>(
      "Cow", [](Cow &) { ImGui::TextDisabled("(tag)"); });
}

FarmScene::FarmScene(std::string name) : Scene(std::move(name)) {
  register_debug_widgets();
}

void FarmScene::on_init() {
  using namespace skeleton::scripting;

  init_lua();
  lua.new_usertype<Position>("__Position", "pos", &Position::pos);
  lua.new_usertype<Player>("__Player");

  bind_component<Position>(lua, "Position");
  bind_component<Player>(lua, "Player");
  skeleton::audio::bind_audio(lua);

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
  registry.emplace<skeleton::graphics::AnimationPlayer>(player,
                                                        std::move(anim));

  ScriptComponent sc;
  sc.path = "assets/scripts/player.lua";
  sc.env = sol::environment(lua, sol::create, lua.globals());
  registry.emplace<ScriptComponent>(player, std::move(sc));

  const char *cow_anim = "assets/farm rpg assets/Farm Animals/cow_female.lua";
  const skeleton::Vec2 cow_positions[] = {{700, 410}, {740, 350}, {580, 395}};
  for (auto &cow_pos : cow_positions) {
    auto cow = registry.create();
    registry.emplace<Position>(cow, cow_pos);
    registry.emplace<Cow>(cow);
    skeleton::graphics::AnimationPlayer canim;
    canim.load(cow_anim);
    registry.emplace<skeleton::graphics::AnimationPlayer>(cow,
                                                          std::move(canim));
    ScriptComponent csc;
    csc.path = "assets/scripts/cow.lua";
    csc.env = sol::environment(lua, sol::create, lua.globals());
    registry.emplace<ScriptComponent>(cow, std::move(csc));
  }
}

void FarmScene::on_input(SDL_Event &) {}
void FarmScene::on_update(double dt) {
  auto &input = skeleton::input::InputManager::get_instance();
  bool moving = input.held("move_right") || input.held("move_left") ||
                input.held("move_down") || input.held("move_up");

  for (auto [e, pos] : registry.view<Player, Position>().each())
    camera.position = pos.pos;

  auto &audio = skeleton::audio::AudioManager::get_instance();
  if (moving && walk_channel_ < 0)
    walk_channel_ = audio.play("walking", -1);
  else if (!moving && walk_channel_ >= 0) {
    audio.stop_channel(walk_channel_);
    walk_channel_ = -1;
  }
}

void FarmScene::on_fixed_update(double) {}

void FarmScene::on_draw() {
  auto &r = skeleton::graphics::Renderer::get_instance();
  r.set_camera(camera);

  auto view = registry.view<Position, skeleton::graphics::AnimationPlayer>();
  for (auto [e, pos, anim] : view.each()) {
    skeleton::Rect src = anim.current_rect();
    skeleton::Rect dst = {pos.pos.x - 16, pos.pos.y - 16, (float)anim.frame_w(),
                          (float)anim.frame_h()};
    r.draw_texture(anim.current_texture(), &src, &dst, 0.0f,
                   anim.current_flip());
  }
  r.reset_camera();
}

void FarmScene::on_destroy() { registry.clear(); }
