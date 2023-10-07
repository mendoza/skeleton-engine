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

void TestScene::on_update(float dt) {}

void TestScene::draw_debug_window() {
	// Create a window called "My First Tool", with a menu bar.
	bool my_tool_active = true;
	ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
			}
			if (ImGui::MenuItem("Close", "Ctrl+W")) {
				my_tool_active = false;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Generate samples and plot them
	float samples[100];
	for (int n = 0; n < 100; n++)
		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
	ImGui::PlotLines("Samples", samples, 100);

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();
}

void TestScene::on_draw() {}
void TestScene::on_destroy() {}
