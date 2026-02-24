#pragma once
#include <entt/entt.hpp>
#include <functional>
#include <sol/sol.hpp>
#include <string>
#include <unordered_map>

namespace skeleton::scripting {

using GetterFn =
    std::function<sol::object(entt::registry &, entt::entity, sol::state_view)>;
using CheckerFn = std::function<bool(entt::registry &, entt::entity)>;
using EmplacerFn = std::function<void(entt::registry &, entt::entity)>;

inline std::unordered_map<entt::id_type, GetterFn> &component_getters() {
  static std::unordered_map<entt::id_type, GetterFn> map;
  return map;
}

inline std::unordered_map<entt::id_type, CheckerFn> &component_checkers() {
  static std::unordered_map<entt::id_type, CheckerFn> map;
  return map;
}

inline std::unordered_map<entt::id_type, EmplacerFn> &component_emplacers() {
  static std::unordered_map<entt::id_type, EmplacerFn> map;
  return map;
}

struct EntityHandle {
  entt::registry *registry;
  entt::entity entity;

  sol::object get(sol::table token, sol::this_state s) {
    sol::state_view lua(s);
    entt::id_type id = token["__id"].get<entt::id_type>();
    auto it = component_getters().find(id);
    if (it == component_getters().end())
      return sol::make_object(lua, sol::nil);
    return it->second(*registry, entity, lua);
  }

  void emplace(sol::table token) {
    entt::id_type id = token["__id"].get<entt::id_type>();
    auto it = component_emplacers().find(id);
    if (it != component_emplacers().end())
      it->second(*registry, entity);
  }
};

inline void bind_entity_handle(sol::state &lua) {
  lua.new_usertype<EntityHandle>("EntityHandle", "get", &EntityHandle::get,
                                 "emplace", &EntityHandle::emplace);
}

template <typename T>
void bind_component(sol::state &lua, const std::string &name) {
  entt::id_type id = entt::type_hash<T>::value();
  component_getters()[id] = [](entt::registry &reg, entt::entity e,
                               sol::state_view lua) -> sol::object {
    if constexpr (std::is_empty_v<T>) {
      if (reg.all_of<T>(e))
        return sol::make_object(lua, true);
      return sol::make_object(lua, sol::nil);
    } else {
      T *c = reg.try_get<T>(e);
      if (!c)
        return sol::make_object(lua, sol::nil);
      return sol::make_object(lua, c);
    }
  };
  component_checkers()[id] = [](entt::registry &reg, entt::entity e) -> bool {
    return reg.all_of<T>(e);
  };
  component_emplacers()[id] = [](entt::registry &reg, entt::entity e) {
    reg.emplace_or_replace<T>(e);
  };
  sol::table token = lua.create_table();
  token["__id"] = id;
  lua[name] = token;
}

struct ScriptComponent {
  std::string path;
  sol::environment env;
  bool initialized = false;
};

struct SystemScript {
  std::string path;
  sol::environment env;
  bool initialized = false;
};

struct ScriptWorld {
  entt::registry *registry;

  EntityHandle create() { return EntityHandle{registry, registry->create()}; }

  void destroy(EntityHandle handle) {
    if (registry->valid(handle.entity))
      registry->destroy(handle.entity);
  }

  sol::object query(sol::variadic_args args, sol::this_state s) {
    sol::state_view lua(s);

    std::vector<entt::id_type> ids;
    ids.reserve(args.size());
    for (auto arg : args) {
      sol::table token = arg;
      ids.push_back(token["__id"].get<entt::id_type>());
    }

    auto matches = std::make_shared<std::vector<EntityHandle>>();
    auto &checkers = component_checkers();
    for (auto e : registry->storage<entt::entity>()) {
      if (!registry->valid(e))
        continue;
      bool match = true;
      for (auto id : ids) {
        auto it = checkers.find(id);
        if (it == checkers.end() || !it->second(*registry, e)) {
          match = false;
          break;
        }
      }
      if (match)
        matches->push_back({registry, e});
    }

    auto idx = std::make_shared<size_t>(0);
    auto iter = [matches, idx](sol::this_state s2) mutable -> sol::object {
      sol::state_view l(s2);
      if (*idx >= matches->size())
        return sol::make_object(l, sol::nil);
      return sol::make_object(l, (*matches)[(*idx)++]);
    };
    return sol::make_object(lua, sol::as_function(std::move(iter)));
  }
};

inline void bind_script_world(sol::state &lua, entt::registry &registry) {
  lua.new_usertype<ScriptWorld>("__ScriptWorld", "query", &ScriptWorld::query,
                                "create", &ScriptWorld::create, "destroy",
                                &ScriptWorld::destroy);
  lua["world"] = ScriptWorld{&registry};
}

} // namespace skeleton::scripting
