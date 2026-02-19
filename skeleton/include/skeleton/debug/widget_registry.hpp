#pragma once
#include <entt/entt.hpp>
#include <functional>
#include <imgui.h>
#include <string>
#include <unordered_map>

namespace skeleton::debug {

using WidgetFn = std::function<void(entt::registry &, entt::entity)>;

struct WidgetEntry {
    std::string label;
    WidgetFn draw;
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
            if (auto *c = reg.try_get<T>(e)) fn(*c);
        }
    };
}

inline void draw_entity(entt::registry &reg, entt::entity e) {
    for (auto &[id, entry] : widget_map()) {
        entry.draw(reg, e);
    }
}

inline void draw_all_entities(entt::registry &reg) {
    for (auto e : reg.storage<entt::entity>()) {
        ImGui::PushID((int)e);
        if (ImGui::CollapsingHeader(("Entity " + std::to_string((uint32_t)e)).c_str())) {
            draw_entity(reg, e);
        }
        ImGui::PopID();
    }
}

} // namespace skeleton::debug
