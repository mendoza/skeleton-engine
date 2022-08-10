#include <SplashState.hpp>
#include <TestState.hpp>

SplashState::SplashState(skeleton::GameDataRef data) : Data(data) {}

void SplashState::init() {
	L.script_file("assets/scripts/config.lua");
	this->config = L["config"];
	this->Splash = this->config["splash"];
	std::string filePath = this->Splash["backgroud_img_file"];
	this->Data->Assets.loadTexture("Splash State Background", filePath);
	this->Background.setTexture(
		this->Data->Assets.getTexture("Splash State Background"));
}

void SplashState::handleInput(sf::Event event) {}

void SplashState::update(float dt) {
	float Time = this->Splash["time"];
	if (this->Timer.getElapsedTime().asSeconds() > Time) {
		this->Data->Machine.addState(
			skeleton::StateRef(new TestState(this->Data)));
	}
}
void SplashState::drawDebugWindow() {
	ImGui::Begin("Debug Splash.");
	this->Data->logEngine();
	ImGui::Text("Current State: Splash Screen");
	ImGui::End();
	ImGui::EndFrame();
}

void SplashState::draw(float dt) {
	int r = this->Splash["background"]["r"];
	int g = this->Splash["background"]["g"];
	int b = this->Splash["background"]["b"];
	this->Data->Window.clear(sf::Color(r, g, b));
	this->Data->Window.draw(this->Background);
}