#include "BoidsScene.hpp"
#include <algorithm>
#include <imgui.h>
#include <skeleton/core/Logger.hpp>
#include <skeleton/debug/widget_registry.hpp>
#include <skeleton/graphics/Renderer.hpp>
#include <skeleton/input/InputManager.hpp>
#include <skeleton/math/types.hpp>
#include <skeleton/scripting/script_component.hpp>
#include <vector>

struct Position {
  skeleton::Vec2 pos;
};

struct Velocity {
  skeleton::Vec2 vel;
};

struct Leader {};

static skeleton::Vec2 steer_toward(skeleton::Vec2 desired, skeleton::Vec2 current,
                                   float max_speed, float max_force) {
  skeleton::Vec2 s = desired.normalized() * max_speed - current;
  if (s.length() > max_force)
    s = s.normalized() * max_force;
  return s;
}

static void register_debug_widgets() {
  static bool registered = false;
  if (registered) return;
  registered = true;

  skeleton::debug::register_widget<Position>("Position", [](Position &p) {
    ImGui::DragFloat2("pos", &p.pos.x, 0.5f);
  });
  skeleton::debug::register_widget<Velocity>("Velocity", [](Velocity &v) {
    ImGui::DragFloat2("vel", &v.vel.x, 0.5f);
  });
  skeleton::debug::register_widget<Leader>("Leader", [](Leader &) {
    ImGui::TextDisabled("(tag)");
  });
}

BoidsScene::BoidsScene(std::string name) : Scene(std::move(name)) {
  register_debug_widgets();
}

void BoidsScene::on_init() {
  using namespace skeleton::scripting;

  camera.position = {world_w / 2.0f, world_h / 2.0f};

  lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);
  lua.new_usertype<skeleton::Vec2>("Vec2", "x", &skeleton::Vec2::x, "y",
                                   &skeleton::Vec2::y);
  lua.new_usertype<Position>("__Position", "pos", &Position::pos);
  lua.new_usertype<Velocity>("__Velocity", "vel", &Velocity::vel);
  lua.new_usertype<Leader>("__Leader");

  bind_entity_handle(lua);
  bind_component<Position>(lua, "Position");
  bind_component<Velocity>(lua, "Velocity");
  bind_component<Leader>(lua, "Leader");
  bind_script_world(lua, registry);
  skeleton::input::bind_input(lua);

  lua["world_w"] = world_w;
  lua["world_h"] = world_h;

  // flocking params readable/writable from Lua
  lua["perception"] = &perception;
  lua["max_speed"]  = &max_speed;
  lua["max_force"]  = &max_force;
  lua["sep_weight"]  = &sep_weight;
  lua["ali_weight"]  = &ali_weight;
  lua["coh_weight"]  = &coh_weight;
  lua["flee_range"]  = &flee_range;
  lua["flee_weight"] = &flee_weight;

  auto leader_e = registry.create();
  registry.emplace<Position>(leader_e, skeleton::Vec2{world_w / 2.0f, world_h / 2.0f});
  registry.emplace<Velocity>(leader_e, skeleton::Vec2{max_speed, 0.0f});
  registry.emplace<Leader>(leader_e);
  ScriptComponent lsc;
  lsc.path = "assets/scripts/leader.lua";
  lsc.env  = sol::environment(lua, sol::create, lua.globals());
  registry.emplace<ScriptComponent>(leader_e, std::move(lsc));

  auto sys_e = registry.create();
  SystemScript ss;
  ss.path = "assets/scripts/boids_system.lua";
  ss.env  = sol::environment(lua, sol::create, lua.globals());
  registry.emplace<SystemScript>(sys_e, std::move(ss));
}

void BoidsScene::on_input(SDL_Event &event) {
  if (follow_leader)
    return;
  if (event.type == SDL_MOUSEBUTTONDOWN &&
      event.button.button == SDL_BUTTON_MIDDLE) {
    panning      = true;
    last_mouse_x = event.button.x;
    last_mouse_y = event.button.y;
  }
  if (event.type == SDL_MOUSEBUTTONUP &&
      event.button.button == SDL_BUTTON_MIDDLE) {
    panning = false;
  }
  if (event.type == SDL_MOUSEMOTION && panning) {
    camera.position.x -= (float)(event.motion.x - last_mouse_x) / camera.zoom;
    camera.position.y -= (float)(event.motion.y - last_mouse_y) / camera.zoom;
    last_mouse_x = event.motion.x;
    last_mouse_y = event.motion.y;
  }
  if (event.type == SDL_MOUSEWHEEL) {
    float factor = event.wheel.y > 0 ? 1.1f : (1.0f / 1.1f);
    camera.zoom = std::clamp(camera.zoom * factor, 0.1f, 10.0f);
  }
}

void BoidsScene::on_update(double) {
  if (!follow_leader)
    return;
  for (auto [e, pos] : registry.view<Position, Leader>().each()) {
    camera.position = pos.pos;
    break;
  }
}

static void run_flocking(entt::registry &registry, double dt, float perception,
                         float max_speed, float max_force, float sep_weight,
                         float ali_weight, float coh_weight, float flee_range,
                         float flee_weight, float world_w, float world_h) {
  skeleton::Vec2 leader_pos{};
  bool           has_leader = false;
  for (auto [e, lpos] : registry.view<Position, Leader>().each()) {
    leader_pos = lpos.pos;
    has_leader = true;
    break;
  }

  auto view = registry.view<Position, Velocity>();

  struct BoidData {
    skeleton::Vec2 pos, vel;
  };

  // Static vectors persist across frames — no per-frame heap allocation.
  static std::vector<BoidData> snapshot;
  static std::vector<int>      cell_of, cell_count, cell_start, sorted, fill;

  snapshot.clear();
  for (auto [e, pos, vel] : view.each())
    snapshot.push_back({pos.pos, vel.vel});

  int n = (int)snapshot.size();
  if (n == 0)
    return;

  int grid_w  = (int)(world_w / perception) + 1;
  int grid_h  = (int)(world_h / perception) + 1;
  int n_cells = grid_w * grid_h;

  cell_of.resize(n);
  cell_count.assign(n_cells, 0);
  cell_start.resize(n_cells + 1);
  sorted.resize(n);

  for (int i = 0; i < n; i++) {
    int cx     = std::clamp((int)(snapshot[i].pos.x / perception), 0, grid_w - 1);
    int cy     = std::clamp((int)(snapshot[i].pos.y / perception), 0, grid_h - 1);
    cell_of[i] = cy * grid_w + cx;
    cell_count[cell_of[i]]++;
  }
  cell_start[0] = 0;
  for (int i = 0; i < n_cells; i++)
    cell_start[i + 1] = cell_start[i] + cell_count[i];

  fill.assign(cell_start.begin(), cell_start.begin() + n_cells);
  for (int i = 0; i < n; i++)
    sorted[fill[cell_of[i]]++] = i;

  // Squared perception avoids sqrt in the inner loop.
  // sep force: diff.normalized() * (1/dist) == diff / dist² (no sqrt needed).
  const float perc2 = perception * perception;

  for (auto [entity, pos, vel] : view.each()) {
    if (registry.all_of<Leader>(entity))
      continue;

    int cell_x = std::clamp((int)(pos.pos.x / perception), 0, grid_w - 1);
    int cell_y = std::clamp((int)(pos.pos.y / perception), 0, grid_h - 1);

    skeleton::Vec2 sep{}, ali{}, coh{};
    int            neighbors = 0;

    for (int dy = -1; dy <= 1; dy++) {
      for (int dx = -1; dx <= 1; dx++) {
        int nx = cell_x + dx, ny = cell_y + dy;
        if (nx < 0 || nx >= grid_w || ny < 0 || ny >= grid_h)
          continue;
        int cell = ny * grid_w + nx;
        for (int k = cell_start[cell]; k < cell_start[cell + 1]; k++) {
          const auto    &other = snapshot[sorted[k]];
          skeleton::Vec2 diff  = pos.pos - other.pos;
          float          dist2 = diff.length_sq();
          if (dist2 <= 0 || dist2 > perc2)
            continue;
          sep += diff * (1.0f / dist2);  // == diff.normalized() / dist
          ali += other.vel;
          coh += other.pos;
          neighbors++;
        }
      }
    }

    skeleton::Vec2 steering{};
    if (neighbors > 0) {
      steering += steer_toward(sep, vel.vel, max_speed, max_force) * sep_weight;
      steering += steer_toward(ali / (float)neighbors, vel.vel, max_speed, max_force) * ali_weight;
      steering += steer_toward(coh / (float)neighbors - pos.pos, vel.vel, max_speed, max_force) * coh_weight;
    }

    if (has_leader) {
      skeleton::Vec2 away  = pos.pos - leader_pos;
      float          dist2 = away.length_sq();
      if (dist2 > 0 && dist2 < flee_range * flee_range)
        steering += steer_toward(away, vel.vel, max_speed, max_force) * flee_weight;
    }

    vel.vel += steering * (float)dt;
    if (vel.vel.length() > max_speed)
      vel.vel = vel.vel.normalized() * max_speed;

    pos.pos += vel.vel * (float)dt;

    // if (pos.pos.x < 0)       pos.pos.x += world_w;
    // if (pos.pos.x > world_w) pos.pos.x -= world_w;
    // if (pos.pos.y < 0)       pos.pos.y += world_h;
    // if (pos.pos.y > world_h) pos.pos.y -= world_h;
  }
}

void BoidsScene::on_fixed_update(double dt) {
  run_flocking(registry, dt, perception, max_speed, max_force, sep_weight,
               ali_weight, coh_weight, flee_range, flee_weight, world_w, world_h);
  using namespace skeleton::scripting;

  auto sc_view = registry.view<ScriptComponent>();
  for (auto [e, sc] : sc_view.each()) {
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


  auto sys_view = registry.view<SystemScript>();
  for (auto [e, ss] : sys_view.each()) {
    if (!ss.initialized) {
      auto result =
          lua.safe_script_file(ss.path, ss.env, sol::script_pass_on_error);
      if (!result.valid()) {
        sol::error err = result;
        skeleton::core::Logger::error(err.what());
      } else {
        sol::protected_function on_init = ss.env["on_init"];
        if (on_init.valid()) {
          auto r = on_init();
          if (!r.valid()) {
            sol::error err = r;
            skeleton::core::Logger::error(err.what());
          }
        }
      }
      ss.initialized = true;
    }

    sol::protected_function on_update = ss.env["on_update"];
    if (on_update.valid()) {
      auto result = on_update((float)dt);
      if (!result.valid()) {
        sol::error err = result;
        skeleton::core::Logger::error(err.what());
      }
    }
  }
}

void BoidsScene::on_draw() {
  auto &r = skeleton::graphics::Renderer::get_instance();
  r.set_camera(camera);

  auto view = registry.view<Position, Velocity>();
  for (auto [entity, pos, vel] : view.each()) {
    skeleton::Vec2 forward = vel.vel.normalized();
    skeleton::Vec2 right   = {-forward.y, forward.x};
    skeleton::Color color  = registry.all_of<Leader>(entity)
                                 ? skeleton::Color{255, 80, 80, 255}
                                 : skeleton::Color{255, 255, 255, 255};

    skeleton::Vec2 tip = pos.pos + forward * 8.0f;
    skeleton::Vec2 bl  = pos.pos - forward * 5.0f + right * 4.0f;
    skeleton::Vec2 br  = pos.pos - forward * 5.0f - right * 4.0f;

    r.draw_line(tip, bl, color);
    r.draw_line(tip, br, color);
    r.draw_line(bl, br, color);
  }

  r.reset_camera();
}

void BoidsScene::on_destroy() { registry.clear(); }

void BoidsScene::on_debug_ui() {
  ImGui::Begin("Boids");
  ImGui::SliderFloat("Perception", &perception, 10.0f, 200.0f);
  ImGui::SliderFloat("Max Speed",  &max_speed,  30.0f, 400.0f);
  ImGui::SliderFloat("Max Force",  &max_force,  10.0f, 500.0f);
  ImGui::SliderFloat("Separation", &sep_weight, 0.0f, 5.0f);
  ImGui::SliderFloat("Alignment",  &ali_weight, 0.0f, 5.0f);
  ImGui::SliderFloat("Cohesion",   &coh_weight,  0.0f,   5.0f);
  ImGui::SliderFloat("Flee Range", &flee_range,  0.0f, 400.0f);
  ImGui::SliderFloat("Flee",       &flee_weight, 0.0f,  10.0f);

  ImGui::Separator();
  ImGui::Text("Camera");
  if (ImGui::Checkbox("Follow Leader", &follow_leader))
    panning = false;
  if (!follow_leader)
    ImGui::DragFloat2("Position", &camera.position.x, 1.0f);
  ImGui::SliderFloat("Zoom", &camera.zoom, 0.1f, 10.0f, "%.2fx");
  if (ImGui::Button("Reset Camera")) {
    camera.position = {world_w / 2.0f, world_h / 2.0f};
    camera.zoom     = 1.0f;
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("Entities"))
    skeleton::debug::draw_all_entities(registry);

  ImGui::End();
}
