#include <SplashScene.hpp>
// #include <TestScene.hpp>

SplashScene::SplashScene() {}

void SplashScene::on_init() {
	L.script_file("assets/scripts/config.lua");
	this->config = L["config"];
	this->splash = this->config["splash"];
	std::string file_path = this->splash["backgroud_img_file"];
}

void SplashScene::on_input(SDL_Event &event) {}

void SplashScene::on_update(float dt) {
	float Time = this->splash["time"];
	if ((this->initial_time - SDL_GetPerformanceCounter()) > Time) {
		// this->data->state_machine->add_scene(
		// 	std::move(new TestScene()));
	}
}
void SplashScene::create_debug_window() {
	// ImGui::Begin("Debug Splash.");
	// this->data->log_engine();
	// ImGui::Text("Current State: Splash Screen");
	// ImGui::End();
	// ImGui::EndFrame();
}

void SplashScene::on_draw() {
	int r = this->splash["background"]["r"];
	int g = this->splash["background"]["g"];
	int b = this->splash["background"]["b"];
	// Get window surface
	// this->data->screenSurface = SDL_GetWindowSurface(this->data->window);

	// // Fill the surface white
	// SDL_FillRect(this->data->screenSurface, NULL,
	// 			 SDL_MapRGB(this->data->screenSurface->format, r, g, b));
}

void SplashScene::on_destroy() {}