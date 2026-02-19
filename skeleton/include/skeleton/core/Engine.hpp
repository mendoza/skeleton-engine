#pragma once
#include <skeleton/core/Scene.hpp>
#include <string>

namespace skeleton::core {

class Engine {
public:
    Engine(bool debug_mode);
    ~Engine();

    void build_window(int width, int height, const std::string &title,
                      const std::string &icon, bool fullscreen);
    void add_scene(SceneRef scene);
    void run();

private:
    bool is_running = true;
    bool debug_mode;
};

} // namespace skeleton::core
