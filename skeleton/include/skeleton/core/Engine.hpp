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
  // Set the fixed-update rate (default 60). Call before run().
  void set_fixed_hz(int hz) { fixed_dt_ = 1.0 / hz; }
  void run();

private:
  bool is_running = true;
  bool debug_mode;
  double fixed_dt_ = 1.0 / 60.0;

  static constexpr int kFrameHistorySize = 120;
  float frame_times_[kFrameHistorySize] = {};
  int frame_head_ = 0;
};

} // namespace skeleton::core
