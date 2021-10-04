#include <SplashState.hpp>

SplashState::SplashState(Skeleton::GameDataRef data) : Data(data) {}

void SplashState::init() {
	this->Script.script_file("scripts/MetaData.lua");
	this->Meta = this->Script["MetaData"];
	this->Splash = this->Script["MetaData"]["splash"];
	std::string filePath = this->Splash["backgroundImageFile"];
	this->Data->Assets.loadTexture("Splash State Background", filePath);
	this->Background.setTexture(
		this->Data->Assets.getTexture("Splash State Background"));
}

void SplashState::handleInput() {
	sf::Event event;
	while (this->Data->Window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);
		if (sf::Event::Closed == event.type) {
			this->Data->Window.close();
		}
	}
}

void SplashState::update(float dt) {
	float Time = this->Splash["time"];
	if (this->Clock.getElapsedTime().asSeconds() > Time) {
		std::cout << "End of Splash" << std::endl;
		exit(0);
	}
}

void SplashState::draw() {
	ImGui::SFML::Update(this->Data->Window, this->Clock.restart());
	int r = this->Splash["background"]["r"];
	int g = this->Splash["background"]["g"];
	int b = this->Splash["background"]["b"];
	this->Data->Window.clear(sf::Color(r, g, b));
	this->Data->Window.draw(this->Background);
	if (this->Data->DebugMode) {
		ImGui::Begin("Debug Splash.");
		ImGui::Text("Hello World");
		ImGui::End();
	}
	ImGui::EndFrame();
	ImGui::SFML::Render(this->Data->Window);
	this->Data->Window.display();
}