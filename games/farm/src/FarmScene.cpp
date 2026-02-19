#include "FarmScene.hpp"

FarmScene::FarmScene(std::string name) : Scene(std::move(name)) {}

void FarmScene::on_init() {}
void FarmScene::on_input(SDL_Event &) {}
void FarmScene::on_update(double) {}
void FarmScene::on_fixed_update(double) {}
void FarmScene::on_draw() {}
void FarmScene::on_destroy() { registry.clear(); }
void FarmScene::on_debug_ui() {}
