#include "SplashScene.hpp"

SplashScene::SplashScene(std::string tag) : Scene(tag) {}

SplashScene::~SplashScene() = default;

void SplashScene::initialize() {
  // this->script_manager->load_script_file("assets/scripts/config.lua");
  // this->config = this->script_manager->get_table("config");
  // this->splash = this->config["splash"];
  // this->time_to_change_scene = this->splash["time"];
  // std::string file_path = this->splash["backgroud_img_file"];
  // skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->add_texture(
  //     file_path, "splash_background");
  this->start_time = SDL_GetPerformanceCounter();
}

void SplashScene::handle_input(SDL_Event &event) {}

void SplashScene::update(double dt) {
  uint64_t current_time = SDL_GetPerformanceCounter();
  auto elapsedTime =
      static_cast<double>((current_time - this->start_time) /
                          static_cast<double>(SDL_GetPerformanceFrequency()));
  if (elapsedTime > this->time_to_change_scene) {
    skeleton::ServiceLocator::get<skeleton::SkeletonSceneManager>()->add_scene(
        std::make_unique<TestScene>("Test Scene"), true);
  }
}

void SplashScene::draw_debug_window() {
  ImGui::Begin("Debug Splash.");
  ImGui::Text("Current State: Splash Screen");
  ImGui::End();
  ImGui::EndFrame();
}

void SplashScene::draw() {
  sol::table background = this->splash["background"];
  uint8_t r = background["r"];
  uint8_t g = background["g"];
  uint8_t b = background["b"];
  SDL_SetRenderDrawColor(
      skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->renderer, r,
      g, b, 255);
  skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->draw_texture(
      "splash_background", {}, 200, 200);
}

void SplashScene::destroy() {}
