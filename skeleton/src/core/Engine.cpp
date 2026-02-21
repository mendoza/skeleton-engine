#include <SDL.h>
#include <SDL_image.h>
#include <backends/imgui_impl_sdl2.h>
#include <imgui.h>
#include <skeleton/core/Engine.hpp>
#include <skeleton/core/Logger.hpp>
#include <skeleton/core/SceneManager.hpp>
#include <skeleton/debug/Editor.hpp>
#include <skeleton/debug/widget_registry.hpp>
#include <skeleton/graphics/Renderer.hpp>
#include <skeleton/input/InputManager.hpp>
#include <skeleton/scripting/script_component.hpp>

namespace skeleton::core {

Engine::Engine(bool debug_mode, bool editor_mode)
    : debug_mode(debug_mode || editor_mode), editor_mode(editor_mode) {
  using namespace skeleton::scripting;
  skeleton::debug::register_widget<ScriptComponent>(
      "Script Component", [](ScriptComponent &sc) {
        ImGui::LabelText("path", "%s", sc.path.c_str());
        ImGui::LabelText("initialized", "%s", sc.initialized ? "yes" : "no");
      });
  skeleton::debug::register_widget<SystemScript>(
      "System Script", [](SystemScript &ss) {
        ImGui::LabelText("path", "%s", ss.path.c_str());
        ImGui::LabelText("initialized", "%s", ss.initialized ? "yes" : "no");
      });
}
Engine::~Engine() = default;

void Engine::build_window(int width, int height, const std::string &title,
                          const std::string &icon, bool fullscreen) {
  auto &r = skeleton::graphics::Renderer::get_instance();
  r.create_window(title, width, height, debug_mode);

  if (fullscreen)
    SDL_SetWindowFullscreen(r.get_sdl_window(), SDL_WINDOW_FULLSCREEN_DESKTOP);

  if (!icon.empty()) {
    SDL_Surface *surface = IMG_Load(icon.c_str());
    if (surface) {
      SDL_SetWindowIcon(r.get_sdl_window(), surface);
      SDL_FreeSurface(surface);
    } else {
      Logger::warning("Could not load icon: " + icon);
    }
  }
}

void Engine::add_scene(SceneRef scene) {
  SceneManager::get_instance().add_scene(std::move(scene), false);
}

void Engine::run() {
  skeleton::input::InputManager::get_instance().load_bindings("assets/scripts/bindings.lua");

  skeleton::debug::Editor editor;

  uint64_t NOW = SDL_GetPerformanceCounter();
  uint64_t LAST = 0;
  double dt = 0.0;

  double accumulated = 0.0;
  const double fixed_dt = 1.0 / 60.0;

  while (is_running) {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    dt = (double)(NOW - LAST) / (double)SDL_GetPerformanceFrequency();

    Scene *scene = SceneManager::get_instance().get_active_scene();

    skeleton::input::InputManager::get_instance().new_frame();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (debug_mode)
        ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        is_running = false;
      skeleton::input::InputManager::get_instance().process_event(event);
      if (scene)
        scene->on_input(event);
    }

    accumulated += dt;
    while (accumulated >= fixed_dt) {
      if (scene)
        scene->on_fixed_update(fixed_dt);
      accumulated -= fixed_dt;
    }

    if (scene) {
      scene->on_update(dt);
      auto &r = skeleton::graphics::Renderer::get_instance();

      if (editor_mode) {
        r.begin();
        r.begin_scene_capture();
        scene->on_draw();
        r.end_scene_capture();
        editor.draw(r.get_scene_texture(), scene);
        r.end();
      } else {
        r.begin();
        scene->on_draw();
        if (debug_mode)
          scene->on_debug_ui();
        r.end();
      }
    }
  }

  skeleton::graphics::Renderer::get_instance().shutdown();
}

} // namespace skeleton::core
