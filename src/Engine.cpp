#include "Engine.hpp"
#include "SplashScene.hpp"

namespace skeleton {

Engine::Engine(bool debug_mode) { this->debug_mode = debug_mode; }

Engine::~Engine() = default;

void Engine::build_window(int width, int height, const std::string &Title,
						  const std::string &IconFile, bool fullscreen) {
	skeleton::ServiceLocator::provide<SkeletonRenderer>(
		std::make_unique<SkeletonRenderer>(Title, width, height, debug_mode));

	skeleton::ServiceLocator::provide<SkeletonSceneManager>(
		std::make_unique<SkeletonSceneManager>());

	skeleton::ServiceLocator::get<SkeletonSceneManager>()->add_scene(
		std::make_unique<SplashScene>("Splash Scene"), false);
}

void Engine::run() {
	uint64_t NOW = SDL_GetPerformanceCounter();
	uint64_t LAST = 0;
	const double dt = 1.0 / 45.0; // Fixed time step for physics (e.g., 60 FPS)
	double t = 0.0;
	double accumulator = 0.0;
	// FPS variables
	int frameCount = 0;
	double fps = 0.0;
	double fpsTimer = 0.0;

	while (is_running) {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		double frameTime = (double)((NOW - LAST) * 1000 /
									(double)SDL_GetPerformanceFrequency());

		accumulator += frameTime;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (this->debug_mode) {
				ImGui_ImplSDL2_ProcessEvent(&event);
			}
			skeleton::ServiceLocator::get<SkeletonSceneManager>()
				->get_active_scene()
				->handle_input(event);
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
		fpsTimer += frameTime;

		// Calculate and print FPS (same as before)
		if (fpsTimer >= 1000.0) {
			fps = frameCount / (fpsTimer / 1000.0);

			frameCount = 0;
			fpsTimer = 0.0;
		}

		// Perform fixed updates for physics
		while (accumulator >= dt) {
			skeleton::ServiceLocator::get<SkeletonSceneManager>()
				->get_active_scene()
				->update_physics(dt);
			accumulator -= dt;
			t += dt;
		}

		skeleton::ServiceLocator::get<SkeletonSceneManager>()
			->get_active_scene()
			->update(frameTime); // Update other game logic using frameTime

		skeleton::ServiceLocator::get<SkeletonSceneManager>()
			->get_active_scene()
			->draw();
	}

	skeleton::ServiceLocator::get<SkeletonRenderer>()->shutdown();
	skeleton::ServiceLocator::shutdown_all_services();
}
}; // namespace skeleton
