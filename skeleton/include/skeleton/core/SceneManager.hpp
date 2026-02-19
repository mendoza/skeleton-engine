#pragma once
#include <skeleton/core/Scene.hpp>
#include <stack>

namespace skeleton::core {

class SceneManager {
public:
    static SceneManager &get_instance() {
        static SceneManager instance;
        return instance;
    }

    SceneManager(const SceneManager &) = delete;
    SceneManager &operator=(const SceneManager &) = delete;

    void add_scene(SceneRef scene, bool is_replacing);
    void remove_scene();
    Scene *get_active_scene();

private:
    SceneManager() = default;
    ~SceneManager() = default;

    std::stack<SceneRef> scenes;
};

} // namespace skeleton::core
