#include <SkeletonAssetsManager.hpp>
#include <SkeletonRenderer.hpp>
#include <SkeletonSceneManager.hpp>
#include <SplashScene.hpp>
#include <TestScene.hpp>
SplashScene::SplashScene() {}

SplashScene::~SplashScene() {}

void SplashScene::on_init() {
	L.script_file("assets/scripts/config.lua");
	this->config = L["config"];
	this->splash = this->config["splash"];
	this->time_to_change_scene = this->splash["time"];
	std::string file_path = this->splash["backgroud_img_file"];
	locator.get<skeleton::SkeletonAssetsManager>()->add_texture(
		"splash_background", file_path);
	this->start_time = SDL_GetPerformanceCounter();
}

void SplashScene::on_input(SDL_Event &event) {}

void SplashScene::on_update(float dt) {
	uint64_t current_time = SDL_GetPerformanceCounter();
	double elapsedTime =
		static_cast<double>((current_time - this->start_time) /
							static_cast<double>(SDL_GetPerformanceFrequency()));
	if (elapsedTime > this->time_to_change_scene) {
		locator.get<skeleton::SkeletonSceneManager>()->add_scene(
			std::make_unique<TestScene>());
	}
}
void SplashScene::draw_debug_window() {
	// ImGui::Begin("Debug Splash.");
	// this->data->log_engine();
	// ImGui::Text("Current State: Splash Screen");
	// ImGui::End();
	// ImGui::EndFrame();
}

void SplashScene::on_draw() {
	sol::table background = this->splash["background"];
	float r = background["r"];
	float g = background["g"];
	float b = background["b"];
	SDL_SetRenderDrawColor(locator.get<skeleton::SkeletonRenderer>()->renderer,
						   r, g, b, 255);

	SDL_RenderCopy(locator.get<skeleton::SkeletonRenderer>()->renderer,
				   locator.get<skeleton::SkeletonAssetsManager>()->get_texture(
					   "splash_background"),
				   NULL, NULL);
}

void SplashScene::on_destroy() {}