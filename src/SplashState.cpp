#include <SplashState.hpp>
#include <TestState.hpp>

SplashState::SplashState(skeleton::GameDataRef data) : Data(data) {}

void SplashState::init() {
	this->Script.script_file("assets/scripts/MetaData.lua");
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
	if (this->Timer.getElapsedTime().asSeconds() > Time) {
		this->Data->Machine.addState(
			skeleton::StateRef(new TestState(this->Data)));
	}
}

void SplashState::draw(float dt) {
	if (this->Data->DebugMode) {
		ImGui::SFML::Update(this->Data->Window, sf::seconds(dt));
	}

	int r = this->Splash["background"]["r"];
	int g = this->Splash["background"]["g"];
	int b = this->Splash["background"]["b"];
	this->Data->Window.clear(sf::Color(r, g, b));
	this->Data->Window.draw(this->Background);

	if (this->Data->DebugMode) {
		ImGui::Begin("Debug Splash.");
		this->Data->logEngine();
		ImGui::Text("Current State: Splash Screen");
		ImGui::End();
		ImGui::EndFrame();
		ImGui::SFML::Render(this->Data->Window);
	}
	
	this->Data->Window.display();
}