#include <skeleton/core/Logger.hpp>
#include <skeleton/core/Scene.hpp>
#include <skeleton/graphics/AnimationPlayer.hpp>
#include <skeleton/input/InputManager.hpp>
#include <skeleton/math/types.hpp>
#include <skeleton/scripting/script_component.hpp>

namespace skeleton::core {

Scene::~Scene() { registry.clear(); }

void Scene::init_lua() {
  lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
                     sol::lib::table);
  lua.set_function("print", [](sol::variadic_args va) {
    std::string out;
    for (auto v : va) {
      if (!out.empty())
        out += "\t";
      switch (v.get_type()) {
        case sol::type::string:
          out += v.as<std::string>();
          break;
        case sol::type::number:
          out += std::to_string(v.as<double>());
          break;
        case sol::type::boolean:
          out += v.as<bool>() ? "true" : "false";
          break;
        case sol::type::nil:
          out += "nil";
          break;
        default:
          out += "?";
          break;
      }
    }
    Logger::info(out);
  });
  lua.new_usertype<skeleton::Vec2>("Vec2", "x", &skeleton::Vec2::x, "y",
                                   &skeleton::Vec2::y);
  skeleton::input::bind_input(lua);

  using namespace skeleton::scripting;
  using AP = skeleton::graphics::AnimationPlayer;
  lua.new_usertype<AP>("__AnimationPlayer", "play", &AP::play, "update",
                       &AP::update, "current_clip", &AP::current_clip);
  bind_component<AP>(lua, "AnimationPlayer");
  bind_entity_handle(lua);
  bind_script_world(lua, registry);
}

void Scene::tick_scripts(double dt) {
  using namespace skeleton::scripting;

  auto load_script = [&](sol::environment &env,
                         const std::string &path) -> bool {
    auto result = lua.safe_script_file(path, env, sol::script_pass_on_error);
    if (!result.valid()) {
      sol::error err = result;
      Logger::error(err.what());
      return false;
    }
    return true;
  };

  auto call = [&](sol::environment &env, const char *fn, auto... args) {
    sol::protected_function f = env[fn];
    if (!f.valid())
      return;
    auto r = f(args...);
    if (!r.valid()) {
      sol::error err = r;
      Logger::error(err.what());
    }
  };

  for (auto [e, sc] : registry.view<ScriptComponent>().each()) {
    if (!sc.initialized) {
      if (load_script(sc.env, sc.path))
        call(sc.env, "on_init", EntityHandle{&registry, e});
      sc.initialized = true;
    }
    call(sc.env, "on_update", EntityHandle{&registry, e}, (float)dt);
  }

  for (auto [e, ss] : registry.view<SystemScript>().each()) {
    if (!ss.initialized) {
      if (load_script(ss.env, ss.path))
        call(ss.env, "on_init");
      ss.initialized = true;
    }
    call(ss.env, "on_update", (float)dt);
  }
}

void Scene::exec_lua(const std::string &code) {
  auto result = lua.safe_script(code, sol::script_pass_on_error);
  if (!result.valid()) {
    sol::error err = result;
    Logger::error(err.what());
  }
}

} // namespace skeleton::core
