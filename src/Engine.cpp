#include <Engine.hpp>
#include <SplashState.hpp>

namespace skeleton {
Engine::Engine(bool DebugMode) {
	this->Data->DebugMode = DebugMode;
	ImGui::SFML::Init(this->Data->Window);
	this->Data->Machine.addState(StateRef(new SplashState(this->Data)));
}

void Engine::buildWindow(int Width, int Height, std::string Title,
						 std::string IconFile, int Limit, bool VSync) {
	sf::Image image;
	image.loadFromFile(IconFile);
	this->Data->Window.create(sf::VideoMode(Width, Height), Title,
							  sf::Style::Titlebar | sf::Style::Close);
	this->Data->Window.setVerticalSyncEnabled(VSync);
	this->Data->Window.setIcon(image.getSize().x, image.getSize().y,
							   image.getPixelsPtr());
	this->Data->Window.setFramerateLimit(Limit);

	this->Data->setMetaData(Width, Height, Limit, VSync);

	this->run();
}

void Engine::run() {
	float frametime = 0.0f;
	float accumulator = 0.0f;
	while (this->Data->Window.isOpen()) {
		this->Data->Machine.processStateChanges();
		while (accumulator > dt) {
			accumulator -= dt;
			this->Data->Machine.getActiveState()->update(dt);
			this->Data->Machine.getActiveState()->handleInput();
		}
		frametime = this->Clock.restart().asSeconds();
		accumulator += frametime;
		this->Data->FPS = 1.0f / frametime;
		this->Data->Machine.getActiveState()->draw();
	}
	ImGui::SFML::Shutdown();
}
}; // namespace skeleton
