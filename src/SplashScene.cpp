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
	std::string file_path = this->splash["backgroud_img_file"];
	locator.get<skeleton::SkeletonAssetsManager>()->add_texture(
		"splash_background", file_path);
}

void SplashScene::on_input(SDL_Event &event) {}

void SplashScene::on_update(float dt) {
	float Time = this->splash["time"];
	if ((this->initial_time - SDL_GetPerformanceCounter()) > Time) {
		locator.get<skeleton::SkeletonSceneManager>()->add_scene(
			std::make_unique<TestScene>());
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
	float r = this->splash["background"]["r"];
	float g = this->splash["background"]["g"];
	float b = this->splash["background"]["b"];
	SDL_SetRenderDrawColor(locator.get<skeleton::SkeletonRenderer>()->renderer,
						   r, g, b, 255);

	SDL_RenderCopy(locator.get<skeleton::SkeletonRenderer>()->renderer,
				   locator.get<skeleton::SkeletonAssetsManager>()->get_texture(
					   "splash_background"),
				   NULL, NULL);
}

void SplashScene::on_destroy() {}