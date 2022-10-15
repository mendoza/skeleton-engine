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
	this->Data->Window.create(
		sf::VideoMode(sf::VideoMode::getDesktopMode().width,
					  sf::VideoMode::getDesktopMode().height),
		Title, sf::Style::Fullscreen);
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
		this->Data->Machine.processStateChanges();
		newTime = this->Clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f) {
			frameTime = 0.25;
		}
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt) {
			this->Data->Machine.getActiveState()->handleInput();
			this->Data->Machine.getActiveState()->update(dt);
			accumulator -= dt;
		}
		interpolation = accumulator / dt;
		this->Data->FPS = 1.0f / frameTime;
		if (this->Data->DebugMode)
			ImGui::SFML::Update(this->Data->Window, deltaClock.restart());
		this->Data->Window.clear(sf::Color(125, 125, 125));
		if (this->Data->DebugMode)
			this->Data->Machine.getActiveState()->setupDebugWindow();
		this->Data->Machine.getActiveState()->draw(interpolation);
		if (this->Data->DebugMode)
			ImGui::SFML::Render(this->Data->Window);
		this->Data->Window.display();
	}
	ImGui::SFML::Shutdown();
}
}; // namespace skeleton
