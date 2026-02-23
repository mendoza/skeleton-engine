#pragma once
#include <SDL.h>
#include <entt/entt.hpp>
#include <string>

namespace skeleton::core {

class Scene {
public:
    explicit Scene(std::string name) : name(std::move(name)) {}
    virtual ~Scene() = default;

    virtual void on_init() = 0;
    virtual void on_input(SDL_Event &event) = 0;
    virtual void on_update(double dt) = 0;
    virtual void on_fixed_update(double dt) = 0;
    virtual void on_draw() = 0;
    virtual void on_destroy() = 0;
    virtual void on_debug_ui() {}

    const std::string &get_name() const { return name; }
    entt::registry &get_registry() { return registry; }

protected:
    entt::registry registry;
    std::string name;
};

using SceneRef = std::unique_ptr<Scene>;

} // namespace skeleton::core
