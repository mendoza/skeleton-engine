#include <skeleton/core/Logger.hpp>
#include <skeleton/core/Scene.hpp>
#include <skeleton/graphics/AnimationPlayer.hpp>
#include <skeleton/scripting/script_component.hpp>

namespace skeleton::core {

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
  for (auto [e, sc] : registry.view<ScriptComponent>().each()) {
    if (!sc.initialized) {
      auto result =
          lua.safe_script_file(sc.path, sc.env, sol::script_pass_on_error);
      if (!result.valid()) {
        sol::error err = result;
        Logger::error(err.what());
      } else {
        sol::protected_function on_init = sc.env["on_init"];
        if (on_init.valid()) {
          EntityHandle handle{&registry, e};
          auto r = on_init(handle);
          if (!r.valid()) {
            sol::error err = r;
            Logger::error(err.what());
          }
        }
      }
      sc.initialized = true;
    }
    sol::protected_function on_update = sc.env["on_update"];
    if (on_update.valid()) {
      EntityHandle handle{&registry, e};
      auto r = on_update(handle, (float)dt);
      if (!r.valid()) {
        sol::error err = r;
        Logger::error(err.what());
      }
    }
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
