#include <SplashState.hpp>
#include <TestState.hpp>

SplashState::SplashState(skeleton::GameDataRef data) : State(data) {}

void SplashState::on_init() {
	L.script_file("assets/scripts/config.lua");
	this->config = L["config"];
	this->splash = this->config["splash"];
	std::string file_path = this->splash["backgroud_img_file"];
	this->data->asset_manager.load_texture("Splash State Background",
										   file_path);
	this->background.setTexture(
		this->data->asset_manager.get_texture("Splash State Background"));
}

void SplashState::on_input(sf::Event event) {}

void SplashState::on_update(float dt) {
	float Time = this->splash["time"];
	if (this->clock.getElapsedTime().asSeconds() > Time) {
		this->data->state_machine->add_state(
			skeleton::StateRef(new TestState(this->data)));
	}
}
void SplashState::create_debug_window() {
	ImGui::Begin("Debug Splash.");
	this->data->log_engine();
	ImGui::Text("Current State: Splash Screen");
	ImGui::End();
	ImGui::EndFrame();
}

void SplashState::on_draw() {
	int r = this->splash["background"]["r"];
	int g = this->splash["background"]["g"];
	int b = this->splash["background"]["b"];
	this->data->render_window.clear(sf::Color(r, g, b));
	this->data->render_window.draw(this->background);
}