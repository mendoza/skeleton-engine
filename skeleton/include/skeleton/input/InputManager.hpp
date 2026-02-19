#pragma once
#include <SDL.h>
#include <array>
#include <skeleton/math/types.hpp>
#include <sol/sol.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace skeleton::input {

// Mouse buttons are mapped into the key state array starting at this offset,
// so the action binding system (held/pressed/released) works for mouse too.
// Use "Mouse1", "Mouse2", "Mouse3" as key names in bindings.
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

  // Map an action name to a key or mouse button ("W", "Space", "Up", "Mouse1"...).
  // Call multiple times to add multiple inputs to the same action.
  void bind(const std::string &action, const std::string &key_name);

  // Call once per frame before polling SDL events.
  void new_frame();

  // Feed each SDL_Event in from the engine loop.
  void process_event(const SDL_Event &event);

  bool held(const std::string &action) const;
  bool pressed(const std::string &action) const;
  bool released(const std::string &action) const;

  skeleton::Vec2 mouse_pos() const { return mouse_pos_; }
  skeleton::Vec2 mouse_delta() const { return mouse_delta_; }
  float scroll() const { return scroll_; }

  // Load a Lua file that calls input:bind(...). The engine calls this automatically
  // with "assets/scripts/bindings.lua" at the start of run().
  void load_bindings(const std::string &path);

  // Draw an ImGui window showing all bound actions and their current state.
  void debug_ui() const;

private:
  InputManager() = default;

  std::unordered_map<std::string, std::vector<int>> bindings_;
  std::array<bool, KEY_STATE_SIZE> current_{};
  std::array<bool, KEY_STATE_SIZE> previous_{};

  skeleton::Vec2 mouse_pos_{};
  skeleton::Vec2 mouse_delta_{};
  float scroll_{};
};

inline void bind_input(sol::state &lua) {
  lua.new_usertype<InputManager>("__InputManager",
    "bind", &InputManager::bind,
    "held", &InputManager::held,
    "pressed", &InputManager::pressed,
    "released", &InputManager::released,
    "mouse_pos", &InputManager::mouse_pos,
    "mouse_delta", &InputManager::mouse_delta,
    "scroll", &InputManager::scroll
  );
  lua["input"] = &InputManager::get_instance();
}

} // namespace skeleton::input
