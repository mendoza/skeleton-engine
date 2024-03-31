#include "Engine.hpp"
#include "Renderer.hpp"
#include "SceneManager.hpp"

namespace skeleton {

Engine::Engine(bool debug_mode) { this->debug_mode = debug_mode; }

Engine::~Engine() = default;

void Engine::build_window(int width, int height, const std::string &Title,
                          const std::string &IconFile, bool fullscreen) {
  skeleton::Renderer::get_instance().create_window(Title, width, height,
                                                   debug_mode);
}

void Engine::run() {
  uint64_t NOW = SDL_GetPerformanceCounter();
  uint64_t LAST = 0;
  double deltaTime = 0.0;
  // double totalElapsedtime = 0.0;
  const double fixed_dt = 1.0 / 60.0; // once every 60 frames a physics
  // update

  // FPS variables
  int frameCount = 0;
  double fps = 0.0;
  double fpsTimer = 0.0;
  double totalElapsedtime = 0.0;

  while (is_running) {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    // Calculate the time since the last frame in seconds
    deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
    Scene *active_scene =
        skeleton::SceneManager::get_instance().get_active_scene();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (this->debug_mode) {
        ImGui_ImplSDL2_ProcessEvent(&event);
      }
      active_scene->handle_input(event);
      switch (event.type) {
        case SDL_QUIT: {
          is_running = false;
          break;
        }
        default: {
          break;
        }
      }
    }

    // Update FPS-related variables
    frameCount++;
    fpsTimer += deltaTime;

    // Calculate and print FPS
    if (fpsTimer >= 5.0) {
      fps = frameCount / fpsTimer;
      std::cout << "fps: " << fps << std::endl;
      frameCount = 0;
      fpsTimer = 0.0;
    }

    // Accumulate time for physics updates
    totalElapsedtime += deltaTime;

    // Perform physics updates with a variable time step
    while (totalElapsedtime >= fixed_dt) {
      active_scene->fixed_update(fixed_dt);
      totalElapsedtime -= fixed_dt;
    }

    // Update game logic using deltaTime
    active_scene->update(deltaTime);

    // Draw the scene
    active_scene->draw();
  }

  // Cleanup
  skeleton::Renderer::get_instance().shutdown();
  // skeleton::SceneManager::get_instance().shutdown();
}
}; // namespace skeleton
