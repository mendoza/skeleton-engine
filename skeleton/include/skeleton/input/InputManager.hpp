#pragma once
#include <SDL.h>
#include <array>
#include <deque>
#include <skeleton/math/types.hpp>
#include <sol/sol.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace skeleton::input {

static constexpr int MOUSE_OFFSET = SDL_NUM_SCANCODES;
static constexpr int KEY_STATE_SIZE = SDL_NUM_SCANCODES + 5;

class InputManager {
public:
  static InputManager &get_instance() {
    static InputManager instance;
    return instance;
  }
  InputManager(const InputManager &) = delete;
  InputManager &operator=(const InputManager &) = delete;

  void bind(const std::string &action, const std::string &key_name);
  void new_frame();
  void process_event(const SDL_Event &event);

  bool held(const std::string &action) const;
  bool pressed(const std::string &action) const;
  bool released(const std::string &action) const;

  skeleton::Vec2 mouse_pos() const { return mouse_pos_; }
  skeleton::Vec2 mouse_delta() const { return mouse_delta_; }
  float scroll() const { return scroll_; }

  void load_bindings(const std::string &path);

private:
  InputManager() = default;

  std::unordered_map<std::string, std::vector<int>> bindings_;
  std::array<bool, KEY_STATE_SIZE> current_{};
  std::array<bool, KEY_STATE_SIZE> previous_{};

  skeleton::Vec2 mouse_pos_{};
  skeleton::Vec2 mouse_delta_{};
  float scroll_{};

  static constexpr size_t kEventLogMax = 200;
  std::deque<std::string> event_log_;
};

inline void bind_input(sol::state &lua) {
  lua.new_usertype<InputManager>(
      "__InputManager", "bind", &InputManager::bind, "held",
      &InputManager::held, "pressed", &InputManager::pressed, "released",
      &InputManager::released, "mouse_pos", &InputManager::mouse_pos,
      "mouse_delta", &InputManager::mouse_delta, "scroll",
      &InputManager::scroll);
  lua["input"] = &InputManager::get_instance();
}

} // namespace skeleton::input
