#include <Engine.hpp>
#include <SplashState.hpp>

namespace skeleton {

Engine::Engine(bool debug_mode) {
	this->data->debug_mode = debug_mode;
	this->data->set_state_machine(new StateMachine());
	this->data->machine->add_state(StateRef(new SplashState(this->data)));
}

void Engine::build_window(sf::Vector2u resolution, std::string Title,
						 std::string IconFile, bool fullscreen) {
	sf::Image image;
	image.loadFromFile(IconFile);
	if (fullscreen) {
		this->data->render_window.create(
			sf::VideoMode(sf::VideoMode::getDesktopMode().width,
						  sf::VideoMode::getDesktopMode().height),
			Title, sf::Style::Fullscreen);
	} else {
		this->data->render_window.create(
			sf::VideoMode(resolution.x, resolution.y),
			Title, sf::Style::Fullscreen);
	}

	this->data->render_window.setIcon(image.getSize().x, image.getSize().y,
							   image.getPixelsPtr());

	if (this->data->debug_mode)
		ImGui::SFML::Init(this->data->render_window);

	this->run();
}

void Engine::run() {
	float newTime, frameTime, interpolation = 0.0f;
	float currentTime = this->clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	sf::Clock deltaClock;
	while (this->data->render_window.isOpen()) {
		this->data->machine->process_state_changes();
		newTime = this->clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f) {
			frameTime = 0.25;
		}
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt) {
			this->data->machine->get_active_state()->handle_input();
			this->data->machine->get_active_state()->update(dt);
			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->data->fps = 1.0f / frameTime;

		if (this->data->debug_mode)
			ImGui::SFML::Update(this->data->render_window, deltaClock.restart());
		
		this->data->render_window.clear(sf::Color(125, 125, 125));
		
		if (this->data->debug_mode)
			this->data->machine->get_active_state()->create_debug_window();

		this->data->machine->get_active_state()->draw(interpolation);

		if (this->data->debug_mode)
			ImGui::SFML::Render(this->data->render_window);

		this->data->render_window.display();
	}
	ImGui::SFML::Shutdown();
}
}; // namespace skeleton
