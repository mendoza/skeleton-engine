#include <Engine.hpp>
#include <SplashState.hpp>

namespace skeleton {

Engine::Engine(bool DebugMode) {
	this->Data->DebugMode = DebugMode;
	this->Data->Machine.addState(StateRef(new SplashState(this->Data)));
}

void Engine::buildWindow(int Width, int Height, std::string Title,
						 std::string IconFile) {
	sf::Image image;
	image.loadFromFile(IconFile);
	this->Data->Window.create(sf::VideoMode(Width, Height), Title,
							  sf::Style::Titlebar | sf::Style::Close |
								  sf::Style::Resize);
	this->Data->Window.setIcon(image.getSize().x, image.getSize().y,
							   image.getPixelsPtr());

	if (this->Data->DebugMode)
		ImGui::SFML::Init(this->Data->Window);

	this->run();
}

void Engine::run() {
	float newTime, frameTime, interpolation = 0.0f;
	float currentTime = this->Clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	sf::Clock deltaClock;
	while (this->Data->Window.isOpen()) {
		sf::Event event;
		this->Data->Machine.processStateChanges();
		newTime = this->Clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f) {
			frameTime = 0.25;
		}
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt) {
			while (this->Data->Window.pollEvent(event)) {
				ImGui::SFML::ProcessEvent(event);

				if (event.type == sf::Event::Closed) {
					this->Data->Window.close();
				}

				if (event.type == sf::Event::Resized) {
					// update the view to the new size of the window
					sf::FloatRect visibleArea(0, 0, event.size.width,
											  event.size.height);
					this->Data->Window.setView(sf::View(visibleArea));
				}

				this->Data->Machine.getActiveState()->handleInput(event);
			}

			this->Data->Machine.getActiveState()->update(dt);
			accumulator -= dt;
		}
		interpolation = accumulator / dt;
		this->Data->FPS = 1.0f / frameTime;
		ImGui::SFML::Update(this->Data->Window, deltaClock.restart());
		this->Data->Window.clear(sf::Color(125, 125, 125));
		if (this->Data->DebugMode)
			this->Data->Machine.getActiveState()->drawDebugWindow();
		this->Data->Machine.getActiveState()->draw(interpolation);
		ImGui::SFML::Render(this->Data->Window);
		this->Data->Window.display();
	}
	ImGui::SFML::Shutdown();
}
}; // namespace skeleton
