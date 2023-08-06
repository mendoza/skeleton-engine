#include <Engine.hpp>
#include <SplashScene.hpp>

namespace skeleton {

Engine::Engine(bool debug_mode) {
	this->data->debug_mode = debug_mode;
	this->data->set_state_machine(new SceneManager());
}

void Engine::build_window(uint32_t width, uint32_t height, std::string Title,
						  std::string IconFile, bool fullscreen) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	SDL_Window *window = SDL_CreateWindow(
		Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
		height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	SDL_Renderer *renderer =
		SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	locator.provide<SkeletonRenderer>(
		std::make_unique<SkeletonRenderer>(window, renderer));

	this->data->state_machine->add_scene(std::make_unique<SplashScene>());
	// if (this->data->debug_mode)
	// 	ImGui::SFML::Init(this->data->render_window);

	this->run();
}

void Engine::run() {
	uint64_t NOW = SDL_GetPerformanceCounter();
	uint64_t LAST = 0;
	double deltaTime = 0;
	while (this->data->is_running) {
		this->data->state_machine->process_scene_changes();

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 /
							 (double)SDL_GetPerformanceFrequency());

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// if (this->data->debug_mode)
			// 	ImGui::SFML::ProcessEvent(event);
			this->data->state_machine->get_active_scene()->handle_input(event);
			switch (event.type) {
				case SDL_QUIT: {
					this->data->is_running = false;
					break;
				}

				default: {
					break;
				}
			}
		}

		this->data->state_machine->get_active_scene()->update(deltaTime);

		this->data->fps = 1.0f / deltaTime;

		// if (this->data->debug_mode)
		// ImGui::SFML::Update(this->data->render_window,
		// 					deltaClock.restart());

		// this->data->render_window.clear(sf::Color(125, 125, 125));
		locator.get<SkeletonRenderer>()->clear();

		if (this->data->debug_mode)
			this->data->state_machine->get_active_scene()
				->create_debug_window();

		this->data->state_machine->get_active_scene()->draw();

		// if (this->data->debug_mode)
		// 	ImGui::SFML::Render(this->data->render_window);
		locator.get<SkeletonRenderer>()->update();
	}
	// ImGui::SFML::Shutdown();
	SDL_DestroyWindow(locator.get<SkeletonRenderer>()->window);
	SDL_Quit();
}
}; // namespace skeleton
