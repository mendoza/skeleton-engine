#include <SDL.h>
#include <SDL_image.h>
#include <backends/imgui_impl_sdl2.h>
#include <fstream>
#include <imgui.h>
#include <skeleton/audio/AudioManager.hpp>
#include <skeleton/core/Engine.hpp>
#include <skeleton/core/Logger.hpp>
#include <skeleton/core/SceneManager.hpp>
#include <skeleton/debug/widget_registry.hpp>
#include <skeleton/graphics/Renderer.hpp>
#include <skeleton/input/InputManager.hpp>
#include <skeleton/scripting/script_component.hpp>

namespace skeleton::core {

Engine::Engine(bool debug_mode) : debug_mode(debug_mode) {
  using namespace skeleton::scripting;
  skeleton::debug::register_widget<ScriptComponent>(
      "Script Component", [](ScriptComponent &sc) {
        ImGui::Text("path: %s", sc.path.c_str());
        ImGui::Text("initialized: %s", sc.initialized ? "yes" : "no");
        if (ImGui::Button("Reload"))
          sc.initialized = false;
      });
  skeleton::debug::register_widget<SystemScript>(
      "System Script", [](SystemScript &ss) {
        ImGui::Text("path: %s", ss.path.c_str());
        ImGui::Text("initialized: %s", ss.initialized ? "yes" : "no");
      });

  if (debug_mode) {
    skeleton::debug::register_global_widget("Log", []() {
      static bool auto_scroll = true;
      if (ImGui::Button("Clear"))
        skeleton::core::Logger::clear();
      ImGui::SameLine();
      ImGui::Checkbox("Auto-scroll", &auto_scroll);
      ImGui::BeginChild("##log", {0, 120}, false,
                        ImGuiWindowFlags_HorizontalScrollbar);
      for (const auto &e : skeleton::core::Logger::entries()) {
        ImVec4 col;
        switch (e.level) {
          case skeleton::core::Logger::Level::Warning:
            col = {1.0f, 0.85f, 0.0f, 1.0f};
            break;
          case skeleton::core::Logger::Level::Error:
            col = {1.0f, 0.3f, 0.3f, 1.0f};
            break;
          default:
            col = ImGui::GetStyleColorVec4(ImGuiCol_Text);
            break;
        }
        ImGui::PushStyleColor(ImGuiCol_Text, col);
        ImGui::Text("[%s] %s", e.time.c_str(), e.msg.c_str());
        ImGui::PopStyleColor();
      }
      if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 1.0f)
        ImGui::SetScrollHereY(1.0f);
      ImGui::EndChild();
    });

    skeleton::debug::register_global_widget("Engine Stats", [this]() {
      float sum = 0.0f, peak = 0.0f;
      for (float t : frame_times_) {
        sum += t;
        if (t > peak)
          peak = t;
      }
      float avg_ms = sum / kFrameHistorySize;
      float fps = avg_ms > 0.0f ? 1000.0f / avg_ms : 0.0f;
      ImGui::Text("%.0f fps  avg %.2f ms  peak %.2f ms", fps, avg_ms, peak);
      ImGui::PlotLines("##ft", frame_times_, kFrameHistorySize, frame_head_,
                       nullptr, 0.0f, 50.0f, {-1, 50});
    });
  }
}
Engine::~Engine() = default;

void Engine::build_window(int width, int height, const std::string &title,
                          const std::string &icon, bool fullscreen) {
  Logger::info("Engine::build_window — " + title + " (" +
               std::to_string(width) + "x" + std::to_string(height) + ")");
  auto &r = skeleton::graphics::Renderer::get_instance();
  r.create_window(title, width, height, debug_mode);
  skeleton::audio::AudioManager::get_instance().init();

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
  skeleton::input::InputManager::get_instance().load_bindings(
      "assets/scripts/bindings.lua");
  if (std::ifstream("assets/scripts/audio.lua").good())
    skeleton::audio::AudioManager::get_instance().load_bindings(
        "assets/scripts/audio.lua");

  uint64_t NOW = SDL_GetPerformanceCounter();
  uint64_t LAST = 0;
  double dt = 0.0;

  double accumulated = 0.0;

  while (is_running) {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    dt = (double)(NOW - LAST) / (double)SDL_GetPerformanceFrequency();
    frame_times_[frame_head_] = (float)(dt * 1000.0);
    frame_head_ = (frame_head_ + 1) % kFrameHistorySize;

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
    // Clamp so a slow frame doesn't trigger a cascade of fixed updates
    // that makes the next frame even slower (death spiral).
    if (accumulated > fixed_dt_ * 4)
      accumulated = fixed_dt_ * 4;
    while (accumulated >= fixed_dt_) {
      if (scene) {
        scene->tick_scripts(fixed_dt_);
        scene->on_fixed_update(fixed_dt_);
      }
      accumulated -= fixed_dt_;
    }

    if (scene) {
      scene->on_update(dt);
      auto &r = skeleton::graphics::Renderer::get_instance();
      r.begin();
      scene->on_draw();
      if (debug_mode) {
        ImGuiIO &io = ImGui::GetIO();
        ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always);
        ImGui::SetNextWindowSize({280, io.DisplaySize.y}, ImGuiCond_Always);
        ImGui::Begin("Debug", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_NoBringToFrontOnFocus);
        skeleton::debug::draw_global_widgets();
        scene->on_debug_ui();
        if (ImGui::CollapsingHeader("Entities")) {
          ImGui::Indent();
          skeleton::debug::draw_all_entities(scene->get_registry());
          ImGui::Unindent();
        }

        ImGui::Separator();
        static char console_buf[256] = {};
        static bool console_refocus = false;
        if (console_refocus) {
          ImGui::SetKeyboardFocusHere(0);
          console_refocus = false;
        }
        ImGui::AlignTextToFramePadding();
        ImGui::TextDisabled("lua>");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(-FLT_MIN);
        if (ImGui::InputText("##console", console_buf, sizeof(console_buf),
                             ImGuiInputTextFlags_EnterReturnsTrue)) {
          if (console_buf[0] != '\0') {
            Logger::info(std::string("> ") + console_buf);
            scene->exec_lua(console_buf);
            console_buf[0] = '\0';
          }
          console_refocus = true;
        }
        ImGui::End();
      }
      r.end();
    }
  }

  skeleton::audio::AudioManager::get_instance().shutdown();
  skeleton::graphics::Renderer::get_instance().shutdown();
}

} // namespace skeleton::core
