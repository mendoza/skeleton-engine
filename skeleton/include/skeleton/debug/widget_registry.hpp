#pragma once
#include <entt/entt.hpp>
#include <functional>
#include <imgui.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace skeleton::debug {

using GlobalWidgetFn = std::function<void()>;

inline std::vector<std::pair<std::string, GlobalWidgetFn>> &
global_widget_list() {
  static std::vector<std::pair<std::string, GlobalWidgetFn>> list;
  return list;
}

inline void register_global_widget(std::string label, GlobalWidgetFn fn) {
  global_widget_list().emplace_back(std::move(label), std::move(fn));
}

inline void draw_global_widgets() {
  for (auto &[label, fn] : global_widget_list()) {
    if (ImGui::CollapsingHeader(label.c_str(),
                                ImGuiTreeNodeFlags_DefaultOpen)) {
      ImGui::Indent();
      fn();
      ImGui::Unindent();
    }
  }
}

using WidgetFn = std::function<void(entt::registry &, entt::entity)>;
using HasFn = std::function<bool(entt::registry &, entt::entity)>;

struct WidgetEntry {
  std::string label;
  WidgetFn draw;
  HasFn has;
};

inline std::unordered_map<entt::id_type, WidgetEntry> &widget_map() {
  static std::unordered_map<entt::id_type, WidgetEntry> map;
  return map;
}

template <typename T>
void register_widget(std::string label, std::function<void(T &)> fn) {
  widget_map()[entt::type_hash<T>::value()] = {
      std::move(label),
      [fn](entt::registry &reg, entt::entity e) {
        if constexpr (std::is_empty_v<T>) {
          if (reg.all_of<T>(e)) {
            T dummy{};
            fn(dummy);
          }
        } else {
          if (auto *c = reg.try_get<T>(e))
            fn(*c);
        }
      },
      [](entt::registry &reg, entt::entity e) { return reg.all_of<T>(e); }};
}

// Draw all components present on an entity.
// Components with a registered widget get a CollapsingHeader + widget content.
// Components without a registered widget show their type name in grey.
inline void draw_entity(entt::registry &reg, entt::entity e) {
  static const entt::id_type entity_id = entt::type_hash<entt::entity>::value();
  bool any = false;
  for (auto &&[id, pool] : reg.storage()) {
    if (id == entity_id || !pool.contains(e))
      continue;
    any = true;

    auto wit = widget_map().find(id);
    if (wit != widget_map().end()) {
      if (ImGui::CollapsingHeader(wit->second.label.c_str(),
                                  ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Indent();
        wit->second.draw(reg, e);
        ImGui::Unindent();
      }
    } else {
      std::string_view name = pool.info().name();
      auto pos = name.rfind(':');
      if (pos != std::string_view::npos)
        name = name.substr(pos + 1);
      ImGui::PushStyleColor(ImGuiCol_Text,
                            ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
      ImGui::BulletText("%.*s", (int)name.size(), name.data());
      ImGui::PopStyleColor();
    }
  }
  if (!any)
    ImGui::TextDisabled("No components");
}

inline void draw_all_entities(entt::registry &reg) {
  for (auto e : reg.storage<entt::entity>()) {
    ImGui::PushID((int)e);
    if (ImGui::CollapsingHeader(
            ("Entity " + std::to_string((uint32_t)e)).c_str())) {
      draw_entity(reg, e);
    }
    ImGui::PopID();
  }
}

} // namespace skeleton::debug
