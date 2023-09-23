#include "TestScene.hpp"

TestScene::TestScene(std::string tag) : Scene(tag) {
	srand((unsigned)time(NULL));
}

TestScene::~TestScene() = default;

void TestScene::on_init() {
	setupLuaState();
	skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
		->set_clear_color({0, 0, 0, 100});

	int width = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
					->get_window_width();
	int height = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
					 ->get_window_height();

	this->numCellsHeight = height / this->cellSize;
	this->numCellsWidth = width / this->cellSize;

	this->world = new int[numCellsHeight * numCellsWidth];

	for (int i = 0; i <= numCellsWidth; i++) {
		for (int j = 0; j <= numCellsHeight; j++) {
			world[i * j + j] = (rand() % 100000) > 50 ? 1 : 0;
		}
	}
}

void TestScene::setupLuaState() {
	this->script_manager->load_script_file("assets/scripts/test_state.lua");

	// L.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
					//  sol::lib::io, sol::lib::os);
					 // sol::table ac = L["actor_parameters"];
					 // sol::table gc = ac["graphic_parameters"];
					 // std::string file_path = gc["sprite_filepath"];
					 // std::string texture_name = gc["sprite_name"];

					 // skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->add_texture(
					 // file_path, texture_name);

					 // this->script_on_update = L["on_update"];
					 // this->script_handle_input = L["handle_input"];
}

void TestScene::on_input(SDL_Event &event) {
	//  this->script_handle_input(event);
}

void TestScene::on_update(float dt) {
	//  this->script_on_update(dt);
}
void TestScene::draw_debug_window() {
	// ImGui::Begin("Test State");
	// console.Draw("Console: Test State", &is_open, L);
	// this->data->log_engine();
	// ImGui::TextColored(ImVec4(1, 1, 0, 1), "Actors");
	// ImGui::BeginChild("Scrolling");
	// int count = 0;
	// for (auto entity : Actors.with<GraphicComponent>()) {
	// 	ImGui::Text(
	// 		"Actor %d: %s", count++,
	// 		entity.get<GraphicComponent>().get_current_animation().c_str());
	// }
	// ImGui::EndChild();
	// ImGui::End();
}

void TestScene::on_draw() {}
void TestScene::on_destroy() {}
