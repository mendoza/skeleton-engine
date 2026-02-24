#include <imgui.h>
#include <skeleton/core/Logger.hpp>
#include <skeleton/debug/widget_registry.hpp>
#include <skeleton/input/InputManager.hpp>

namespace skeleton::input {

void InputManager::bind(const std::string &action, const std::string &key_name) {
  if (key_name.rfind("Mouse", 0) == 0) {
    int btn = std::stoi(key_name.substr(5));
    if (btn < 1 || btn > 5) {
      skeleton::core::Logger::warning("InputManager: invalid mouse button \"" + key_name + "\"");
      return;
    }
    bindings_[action].push_back(MOUSE_OFFSET + btn - 1);
    return;
  }
  SDL_Scancode sc = SDL_GetScancodeFromName(key_name.c_str());
  if (sc == SDL_SCANCODE_UNKNOWN) {
    skeleton::core::Logger::warning("InputManager: unknown key name \"" + key_name + "\"");
    return;
  }
  bindings_[action].push_back((int)sc);
}

void InputManager::new_frame() {
  previous_ = current_;
  mouse_delta_ = {};
  scroll_ = 0.0f;
}

void InputManager::process_event(const SDL_Event &event) {
  if (event.type == SDL_KEYDOWN)
    current_[event.key.keysym.scancode] = true;
  else if (event.type == SDL_KEYUP)
    current_[event.key.keysym.scancode] = false;
  else if (event.type == SDL_MOUSEBUTTONDOWN)
    current_[MOUSE_OFFSET + event.button.button - 1] = true;
  else if (event.type == SDL_MOUSEBUTTONUP)
    current_[MOUSE_OFFSET + event.button.button - 1] = false;
  else if (event.type == SDL_MOUSEMOTION) {
    mouse_pos_ = {(float)event.motion.x, (float)event.motion.y};
    mouse_delta_.x += (float)event.motion.xrel;
    mouse_delta_.y += (float)event.motion.yrel;
  } else if (event.type == SDL_MOUSEWHEEL) {
    float y = (float)event.wheel.y;
    if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) y = -y;
    scroll_ += y;
  }
}

bool InputManager::held(const std::string &action) const {
  auto it = bindings_.find(action);
  if (it == bindings_.end()) return false;
  for (auto idx : it->second)
    if (current_[idx]) return true;
  return false;
}

bool InputManager::pressed(const std::string &action) const {
  auto it = bindings_.find(action);
  if (it == bindings_.end()) return false;
  for (auto idx : it->second)
    if (current_[idx] && !previous_[idx]) return true;
  return false;
}

bool InputManager::released(const std::string &action) const {
  auto it = bindings_.find(action);
  if (it == bindings_.end()) return false;
  for (auto idx : it->second)
    if (!current_[idx] && previous_[idx]) return true;
  return false;
}

void InputManager::load_bindings(const std::string &path) {
  sol::state lua;
  lua.new_usertype<InputManager>("__InputManager", "bind", &InputManager::bind);
  lua["input"] = this;
  auto result = lua.safe_script_file(path, sol::script_pass_on_error);
  if (!result.valid()) {
    sol::error err = result;
    skeleton::core::Logger::warning("InputManager: " + std::string(err.what()));
  }

  skeleton::debug::register_global_widget("Input", [this]() {
    ImGui::SeparatorText("Actions");
    for (auto &[action, indices] : bindings_) {
      bool is_held = false;
      for (auto idx : indices)
        if (current_[idx]) { is_held = true; break; }

      if (is_held)
        ImGui::TextColored({0.3f, 1.0f, 0.3f, 1.0f}, "%s", action.c_str());
      else
        ImGui::TextDisabled("%s", action.c_str());

      for (auto idx : indices) {
        ImGui::SameLine();
        if (idx >= MOUSE_OFFSET)
          ImGui::Text("[Mouse%d]", idx - MOUSE_OFFSET + 1);
        else
          ImGui::Text("[%s]", SDL_GetScancodeName((SDL_Scancode)idx));
      }
    }

    ImGui::SeparatorText("Mouse");
    ImGui::Text("pos   (%.0f, %.0f)", mouse_pos_.x, mouse_pos_.y);
    ImGui::Text("delta (%.0f, %.0f)", mouse_delta_.x, mouse_delta_.y);
    ImGui::Text("scroll %.1f", scroll_);
  });
}

} // namespace skeleton::input
