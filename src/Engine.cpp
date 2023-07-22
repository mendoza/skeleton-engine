#include <Engine.hpp>
#include <SplashState.hpp>

namespace skeleton {

Engine::Engine(bool debug_mode) {
	this->data->debug_mode = debug_mode;
	this->data->set_state_machine(new StateMachine());
	this->data->state_machine->add_state(StateRef(new SplashState(this->data)));
}

void Engine::build_window(sf::Vector2u resolution, std::string Title,
						  std::string IconFile, bool fullscreen) {
	sf::Image image;
	image.loadFromFile(IconFile);
	this->data->render_window.setIcon(image.getSize().x, image.getSize().y,
									  image.getPixelsPtr());
	this->data->render_window.setKeyRepeatEnabled(false);

	if (fullscreen) {
		this->data->render_window.create(
			sf::VideoMode(sf::VideoMode::getDesktopMode().width,
						  sf::VideoMode::getDesktopMode().height),
			Title, sf::Style::Fullscreen);
	} else {
		this->data->render_window.create(
			sf::VideoMode(resolution.x, resolution.y), Title,
			sf::Style::Fullscreen);
	}

	if (this->data->debug_mode)
		ImGui::SFML::Init(this->data->render_window);

	this->run();
}

void Engine::run() {
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Clock deltaClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->data->render_window.isOpen()) {
		this->data->state_machine->process_state_changes();

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			sf::Event event;
			while (this->data->render_window.pollEvent(event)) {
				if (this->data->debug_mode)
					ImGui::SFML::ProcessEvent(event);
				this->data->state_machine->get_active_state()->handle_input(
					event);
				switch (event.type) {
					case sf::Event::Closed: {
						this->data->render_window.close();
						break;
					}

					case sf::Event::Resized: {
						sf::FloatRect visibleArea(0, 0, event.size.width,
												  event.size.height);
						this->data->render_window.setView(
							sf::View(visibleArea));
						break;
					}

					default: {
						break;
					}
				}
			}

			this->data->state_machine->get_active_state()->update(
				TimePerFrame.asSeconds());
		}
		this->data->fps = 1.0f / elapsedTime.asSeconds();

		if (this->data->debug_mode)
			ImGui::SFML::Update(this->data->render_window,
								deltaClock.restart());

		this->data->render_window.clear(sf::Color(125, 125, 125));

		if (this->data->debug_mode)
			this->data->state_machine->get_active_state()
				->create_debug_window();

		this->data->state_machine->get_active_state()->draw();

		if (this->data->debug_mode)
			ImGui::SFML::Render(this->data->render_window);

		this->data->render_window.display();
	}
	ImGui::SFML::Shutdown();
}
}; // namespace skeleton
